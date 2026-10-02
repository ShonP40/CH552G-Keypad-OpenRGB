#!/usr/bin/env python3
"""Send test Adalight frames to the keypad without OpenRGB."""

import argparse
import os
import threading
import time


TEST_PATTERNS = (
    ((255, 0, 0), (0, 255, 0), (0, 0, 255)),
    ((0, 255, 255), (255, 0, 255), (255, 255, 0)),
    ((255, 255, 255), (0, 0, 0), (255, 128, 0)),
    ((0, 0, 0), (0, 0, 0), (0, 0, 0)),
)


def make_frame(colors: tuple[tuple[int, int, int], ...]) -> bytes:
    """Build an Adalight frame for exactly three LEDs."""
    payload = bytes(channel for color in colors for channel in color)
    count = len(colors)
    checksum = (count >> 8) ^ (count & 0xFF) ^ 0x55
    return b"Ada" + bytes((count >> 8, count & 0xFF, checksum)) + payload


def write_frame(fd: int, frame: bytes) -> None:
    """Write the complete frame, handling partial serial writes."""
    offset = 0
    while offset < len(frame):
        written = os.write(fd, frame[offset:])
        if written == 0:
            raise OSError("serial port closed while writing")
        offset += written


def open_port(port: str) -> int:
    """Open a macOS serial device without making the main thread uninterruptible."""
    result: list[int | OSError] = []

    def do_open() -> None:
        try:
            result.append(os.open(port, os.O_WRONLY | os.O_NOCTTY | os.O_NONBLOCK))
        except OSError as error:
            result.append(error)

    thread = threading.Thread(target=do_open, daemon=True)
    thread.start()
    thread.join(timeout=3)
    if thread.is_alive():
        raise TimeoutError(
            f"opening {port} timed out; another program may have the port open"
        )
    if not result:
        raise OSError(f"opening {port} returned no result")
    if isinstance(result[0], OSError):
        raise result[0]
    return result[0]


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Send direct Adalight test frames to a three-LED device."
    )
    parser.add_argument(
        "port",
        help="serial port, for example /dev/cu.usbmodemCH55x_kbd_mos1",
    )
    parser.add_argument(
        "--delay",
        type=float,
        default=1.0,
        help="seconds between patterns (default: 1.0)",
    )
    parser.add_argument(
        "--cycles",
        type=int,
        default=0,
        help="number of times to repeat the patterns; 0 means until Ctrl+C (default: 0)",
    )
    args = parser.parse_args()

    if args.delay < 0:
        parser.error("--delay must not be negative")
    if args.cycles < 0:
        parser.error("--cycles must not be negative")

    print(f"Opening {args.port}...", flush=True)
    try:
        # USB CDC does not use a real UART baud rate. Avoid termios setup.
        fd = open_port(args.port)
    except (OSError, TimeoutError) as error:
        parser.exit(1, f"Could not open {args.port}: {error}\n")

    try:
        print("Port opened. Press Ctrl+C to stop.", flush=True)

        cycle = 0
        while args.cycles == 0 or cycle < args.cycles:
            cycle += 1
            for pattern, colors in enumerate(TEST_PATTERNS, start=1):
                frame = make_frame(colors)
                write_frame(fd, frame)
                print(
                    f"Sent {len(frame)} bytes to {args.port}: ",
                    end="",
                    flush=True,
                )
                print(
                    f"cycle {cycle}"
                    + (f"/{args.cycles}" if args.cycles else "")
                    + ", "
                    f"pattern {pattern}/{len(TEST_PATTERNS)}: {frame.hex(' ')}",
                    flush=True,
                )
                time.sleep(args.delay)
    except OSError as error:
        parser.exit(1, f"\nSerial I/O failed: {error}\n")
    except KeyboardInterrupt:
        print("\nStopped.", flush=True)
    finally:
        os.close(fd)


if __name__ == "__main__":
    main()
