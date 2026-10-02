#include "USBconstant.h"

// Device descriptor
__code USB_Descriptor_Device_t DeviceDescriptor = {
    .Header = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

    .USBSpecification = VERSION_BCD(1, 1, 0),
    .Class = 0xEF,
    .SubClass = 0x02,
    .Protocol = 0x01,

    .Endpoint0Size = DEFAULT_ENDP0_SIZE,

    .VendorID = 0x1209,
    .ProductID = 0xc55D,
    .ReleaseNumber = VERSION_BCD(1, 0, 0),

    .ManufacturerStrIndex = 1,
    .ProductStrIndex = 2,
    .SerialNumStrIndex = 3,

    .NumberOfConfigurations = 1};

/** Configuration descriptor structure. This descriptor, located in FLASH
 * memory, describes the usage of the device in one of its supported
 * configurations, including information about any device interfaces and
 * endpoints. The descriptor is read out by the USB host during the enumeration
 * process when selecting a configuration so that the host may correctly
 * communicate with the USB device.
 */
__code USB_Descriptor_Configuration_t ConfigurationDescriptor = {
    .Config = {.Header = {.Size = sizeof(USB_Descriptor_Configuration_Header_t),
                          .Type = DTYPE_Configuration},

               .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
               .TotalInterfaces = 3,

               .ConfigurationNumber = 1,
               .ConfigurationStrIndex = NO_DESCRIPTOR,

               .ConfigAttributes = (USB_CONFIG_ATTR_RESERVED),

               .MaxPowerConsumption = USB_CONFIG_POWER_MA(200)},

    .CDC_IAD = {.Header = {.Size = sizeof(USB_Descriptor_Interface_Association_t),
                           .Type = DTYPE_InterfaceAssociation},
                .FirstInterfaceIndex = 0,
                .TotalInterfaces = 2,
                .Class = CDC_CSCP_CDCClass,
                .SubClass = CDC_CSCP_ACMSubclass,
                .Protocol = CDC_CSCP_ATCommandProtocol,
                .IADStrIndex = NO_DESCRIPTOR},
    .CDC_ControlInterface = {.Header = {.Size = sizeof(USB_Descriptor_Interface_t),
                                             .Type = DTYPE_Interface},
                              .InterfaceNumber = 0,
                              .AlternateSetting = 0,
                              .TotalEndpoints = 1,
                              .Class = CDC_CSCP_CDCClass,
                              .SubClass = CDC_CSCP_ACMSubclass,
                              .Protocol = CDC_CSCP_ATCommandProtocol,
                              .InterfaceStrIndex = NO_DESCRIPTOR},
    .CDC_FunctionalHeader = {
        .Header = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t),
                   .Type = CDC_DTYPE_CSInterface},
        .Subtype = CDC_DSUBTYPE_CSInterface_Header,
        .CDCSpecification = VERSION_BCD(1, 1, 0)},
    .CDC_ACM = {
        .Header = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t),
                   .Type = CDC_DTYPE_CSInterface},
        .Subtype = CDC_DSUBTYPE_CSInterface_ACM,
        .Capabilities = 0x02},
    .CDC_Union = {
        .Header = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t),
                   .Type = CDC_DTYPE_CSInterface},
        .Subtype = CDC_DSUBTYPE_CSInterface_Union,
        .MasterInterfaceNumber = 0,
        .SlaveInterfaceNumber = 1},
    .CDC_NotificationEndpoint = {.Header = {.Size = sizeof(USB_Descriptor_Endpoint_t),
                                                    .Type = DTYPE_Endpoint},
                                         .EndpointAddress = 0x82,
                                         .Attributes = (EP_TYPE_INTERRUPT |
                                                        ENDPOINT_ATTR_NO_SYNC |
                                                        ENDPOINT_USAGE_DATA),
                                         .EndpointSize = 8,
                                         .PollingIntervalMS = 0x40},

    .CDC_DataInterface = {.Header = {.Size = sizeof(USB_Descriptor_Interface_t),
                                             .Type = DTYPE_Interface},
                                  .InterfaceNumber = 1,
                                  .AlternateSetting = 0,
                                  .TotalEndpoints = 2,
                                  .Class = CDC_CSCP_CDCDataClass,
                                  .SubClass = CDC_CSCP_NoDataSubclass,
                                  .Protocol = CDC_CSCP_NoDataProtocol,
                                  .InterfaceStrIndex = NO_DESCRIPTOR},
    .CDC_DataOUTEndpoint = {.Header = {.Size = sizeof(USB_Descriptor_Endpoint_t),
                                               .Type = DTYPE_Endpoint},
                                    .EndpointAddress = 0x03,
                                    .Attributes = (EP_TYPE_BULK |
                                                   ENDPOINT_ATTR_NO_SYNC |
                                                   ENDPOINT_USAGE_DATA),
                                    .EndpointSize = 64,
                                    .PollingIntervalMS = 0},
    .CDC_DataINEndpoint = {.Header = {.Size = sizeof(USB_Descriptor_Endpoint_t),
                                              .Type = DTYPE_Endpoint},
                                   .EndpointAddress = 0x83,
                                   .Attributes = (EP_TYPE_BULK |
                                                  ENDPOINT_ATTR_NO_SYNC |
                                                  ENDPOINT_USAGE_DATA),
                                   .EndpointSize = 64,
                                   .PollingIntervalMS = 0},
    .HID_Interface = {.Header = {.Size = sizeof(USB_Descriptor_Interface_t),
                                 .Type = DTYPE_Interface},
                      .InterfaceNumber = 2,
                      .AlternateSetting = 0,
                      .TotalEndpoints = 2,
                      .Class = HID_CSCP_HIDClass,
                      .SubClass = HID_CSCP_BootSubclass,
                      .Protocol = HID_CSCP_KeyboardBootProtocol,
                      .InterfaceStrIndex = NO_DESCRIPTOR},
    .HID_KeyboardHID = {.Header = {.Size = sizeof(USB_HID_Descriptor_HID_t),
                                   .Type = HID_DTYPE_HID},
                        .HIDSpec = VERSION_BCD(1, 1, 0),
                        .CountryCode = 0,
                        .TotalReportDescriptors = 1,
                        .HIDReportType = HID_DTYPE_Report,
                        .HIDReportLength = sizeof(ReportDescriptor)},
    .HID_ReportINEndpoint = {.Header = {.Size = sizeof(USB_Descriptor_Endpoint_t),
                                        .Type = DTYPE_Endpoint},
                             .EndpointAddress = KEYBOARD_EPADDR,
                             .Attributes = (EP_TYPE_INTERRUPT |
                                            ENDPOINT_ATTR_NO_SYNC |
                                            ENDPOINT_USAGE_DATA),
                             .EndpointSize = KEYBOARD_MOUSE_EPSIZE,
                             .PollingIntervalMS = 10},
    .HID_ReportOUTEndpoint = {.Header = {.Size = sizeof(USB_Descriptor_Endpoint_t),
                                         .Type = DTYPE_Endpoint},
                              .EndpointAddress = KEYBOARD_LED_EPADDR,
                              .Attributes = (EP_TYPE_INTERRUPT |
                                             ENDPOINT_ATTR_NO_SYNC |
                                             ENDPOINT_USAGE_DATA),
                              .EndpointSize = KEYBOARD_MOUSE_EPSIZE,
                              .PollingIntervalMS = 10}};

__code uint8_t ReportDescriptor[] = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,       // USAGE (Keyboard)
    0xa1, 0x01,       // COLLECTION (Application)
    0x85, 0x01,       //   REPORT_ID (1)
    0x05, 0x07,       //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,       //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,       //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x95, 0x08,       //   REPORT_COUNT (8)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x75, 0x08,       //   REPORT_SIZE (8)
    0x81, 0x03,       //   INPUT (Cnst,Var,Abs)
    0x95, 0x06,       //   REPORT_COUNT (6)
    0x75, 0x08,       //   REPORT_SIZE (8)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00, //   LOGICAL_MAXIMUM (255)
    0x05, 0x07,       //   USAGE_PAGE (Keyboard)
    0x19, 0x00,       //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0xe7,       //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x81, 0x00,       //   INPUT (Data,Ary,Abs)
    0x05, 0x08,       //   USAGE_PAGE (LEDs)
    0x19, 0x01,       //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,       //   USAGE_MAXIMUM (Kana)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x95, 0x05,       //   REPORT_COUNT (5)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x91, 0x02,       //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x75, 0x03,       //   REPORT_SIZE (3)
    0x91, 0x03,       //   OUTPUT (Cnst,Var,Abs)
    0xc0,             // END_COLLECTION
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,       // USAGE (Mouse)
    0xa1, 0x01,       // COLLECTION (Application)
    0x09, 0x01,       //   USAGE (Pointer)
    0xa1, 0x00,       //   COLLECTION (Physical)
    0x85, 0x02,       //   REPORT_ID (2)
    0x05, 0x09,       //     USAGE_PAGE (Button)
    0x19, 0x01,       //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,       //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,       //     LOGICAL_MINIMUM (0)
    0x25, 0x01,       //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,       //     REPORT_COUNT (3)
    0x75, 0x01,       //     REPORT_SIZE (1)
    0x81, 0x02,       //     INPUT (Data,Var,Abs)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x75, 0x05,       //     REPORT_SIZE (5)
    0x81, 0x03,       //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     USAGE (X)
    0x09, 0x31,       //     USAGE (Y)
    0x09, 0x38,       //     USAGE (Wheel)
    0x15, 0x81,       //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,       //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,       //     REPORT_SIZE (8)
    0x95, 0x03,       //     REPORT_COUNT (3)
    0x81, 0x06,       //     INPUT (Data,Var,Rel)
    0xc0,             //     END_COLLECTION
    0xc0              // END_COLLECTION
};

// String Descriptors
__code uint8_t LanguageDescriptor[] = {0x04, 0x03, 0x09,
                                       0x04}; // Language Descriptor
__code uint16_t SerialDescriptor[] = {
    // Serial String Descriptor
    (((13 + 1) * 2) | (DTYPE_String << 8)),
    'C',
    'H',
    '5',
    '5',
    'x',
    ' ',
    'k',
    'b',
    'd',
    ' ',
    'm',
    'o',
    's',
};
__code uint16_t ProductDescriptor[] = {
    // Produce String Descriptor
    (((10 + 1) * 2) | (DTYPE_String << 8)),
    'C',
    'H',
    '5',
    '5',
    'x',
    'd',
    'u',
    'i',
    'n',
    'o',
};
__code uint16_t ManufacturerDescriptor[] = {
    // SDCC is little endian
    (((6 + 1) * 2) | (DTYPE_String << 8)), 'D', 'e', 'q', 'i', 'n', 'g',
};
