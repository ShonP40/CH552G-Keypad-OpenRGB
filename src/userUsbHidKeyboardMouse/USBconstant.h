#ifndef __USB_CONST_DATA_H__
#define __USB_CONST_DATA_H__

// clang-format off
#include <stdint.h>
#include "include/ch5xx.h"
#include "include/ch5xx_usb.h"
#include "usbCommonDescriptors/StdDescriptors.h"
#include "usbCommonDescriptors/CDCClassCommon.h"
#include "usbCommonDescriptors/HIDClassCommon.h"
// clang-format on

#define EP0_ADDR 0
#define EP1_ADDR 10
#define EP2_ADDR 138
#define EP3_ADDR 202

#define KEYBOARD_EPADDR 0x81
#define KEYBOARD_LED_EPADDR 0x01
#define KEYBOARD_MOUSE_EPSIZE 9

/** Type define for the device configuration descriptor structure. This must be
 * defined in the application code, as the configuration descriptor contains
 * several sub-descriptors which vary between devices, and which describe the
 * device's usage to the host.
 */
typedef struct {
  USB_Descriptor_Configuration_Header_t Config;

  USB_Descriptor_Interface_Association_t CDC_IAD;
  USB_Descriptor_Interface_t CDC_ControlInterface;
  USB_CDC_Descriptor_FunctionalHeader_t CDC_FunctionalHeader;
  USB_CDC_Descriptor_FunctionalACM_t CDC_ACM;
  USB_CDC_Descriptor_FunctionalUnion_t CDC_Union;
  USB_Descriptor_Endpoint_t CDC_NotificationEndpoint;
  USB_Descriptor_Interface_t CDC_DataInterface;
  USB_Descriptor_Endpoint_t CDC_DataOUTEndpoint;
  USB_Descriptor_Endpoint_t CDC_DataINEndpoint;

  // Keyboard HID Interface
  USB_Descriptor_Interface_t HID_Interface;
  USB_HID_Descriptor_HID_t HID_KeyboardHID;
  USB_Descriptor_Endpoint_t HID_ReportINEndpoint;
  USB_Descriptor_Endpoint_t HID_ReportOUTEndpoint;
} USB_Descriptor_Configuration_t;

extern __code USB_Descriptor_Device_t DeviceDescriptor;
extern __code USB_Descriptor_Configuration_t ConfigurationDescriptor;
extern __code uint8_t ReportDescriptor[];
extern __code uint8_t LanguageDescriptor[];
extern __code uint16_t SerialDescriptor[];
extern __code uint16_t ProductDescriptor[];
extern __code uint16_t ManufacturerDescriptor[];

#endif
