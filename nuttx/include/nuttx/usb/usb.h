/************************************************************************************
 * include/nuttx/usb/usb.h
 *
 *   Copyright (C) 2008, 2009-2010 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <spudmonkey@racsa.co.cr>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __NUTTX_USB_USB_H
#define __NUTTX_USB_USB_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>

/************************************************************************************
 * Preprocessor Definitions
 ************************************************************************************/

/* All 16-bit values must be little-endian */

#define MSBYTE(u16)                             ((u16) >> 8)     /* Get MS byte from uint16_t */
#define LSBYTE(u16)                             ((u16) & 0xff)   /* Get LS byte from uint16_t */

#define GETUINT16(p)                            (((uint16_t)p[1]<<8)|(uint16_t)p[0])
#define GETUINT32(p)                            (((uint32_t)p[3]<<24)|((uint32_t)p[2]<<16)|\
                                                 ((uint32_t)p[1]<<8)|(uint32_t)p[0])

/* USB directions (in endpoint addresses) */

#define USB_DIR_MASK                            (0x80)
#define USB_EPNO_MASK                           (0x7f)
#define USB_DIR_OUT                             (0x00) /* host-to-device */
#define USB_DIR_IN                              (0x80) /* device-to-host */

#define USB_EPNO(addr)                          ((addr) & USB_EPNO_MASK)
#define USB_EPOUT(addr)                         ((addr) | USB_DIR_OUT)
#define USB_EPIN(addr)                          ((addr) | USB_DIR_IN)
#define USB_ISEPIN(addr)                        (((addr) & USB_DIR_MASK) == USB_DIR_IN)
#define USB_ISEPOUT(addr)                       (((addr) & USB_DIR_MASK) == USB_DIR_OUT)

/* Control Setup Packet.  Byte 0=Request */

#define USB_REQ_DIR_IN                          (0x80) /* Bit 7=1: IN */
#define USB_REQ_DIR_OUT                         (0x00) /* Bit 7=0: OUT */

#define USB_REQ_TYPE_MASK                       (0x60) /* Bits 5:6: Request type */
#define USB_REQ_TYPE_STANDARD                   (0x00)
#define USB_REQ_TYPE_CLASS                      (0x20)
#define USB_REQ_TYPE_VENDOR                     (0x40)

#define USB_REQ_RECIPIENT_MASK                  (0x1f) /* Bits 0:4: Recipient */
#define USB_REQ_RECIPIENT_DEVICE                (0x00)
#define USB_REQ_RECIPIENT_INTERFACE             (0x01)
#define USB_REQ_RECIPIENT_ENDPOINT              (0x02)
#define USB_REQ_RECIPIENT_OTHER                 (0x03)

/* Control Setup Packet.  Byte 1=Standard Request Codes */

#define USB_REQ_GETSTATUS                       (0x00)
#define USB_REQ_CLEARFEATURE                    (0x01)
#define USB_REQ_SETFEATURE                      (0x03)
#define USB_REQ_SETADDRESS                      (0x05)
#define USB_REQ_GETDESCRIPTOR                   (0x06)
#define USB_REQ_SETDESCRIPTOR                   (0x07)
#define USB_REQ_GETCONFIGURATION                (0x08)
#define USB_REQ_SETCONFIGURATION                (0x09)
#define USB_REQ_GETINTERFACE                    (0x0a)
#define USB_REQ_SETINTERFACE                    (0x0b)
#define USB_REQ_SYNCHFRAME                      (0x0c)

#define USB_REQ_SETENCRYPTION                   (0x0d) /* Wireless USB */
#define USB_REQ_GETENCRYPTION                   (0x0e)
#define USB_REQ_SETHANDSHAKE                    (0x0f)
#define USB_REQ_GETHANDSHAKE                    (0x10)
#define USB_REQ_SETCONNECTION                   (0x11)
#define USB_REQ_SETSECURITYDATA                 (0x12)
#define USB_REQ_GETSECURITYDATA                 (0x13)
#define USB_REQ_SETWUSBDATA                     (0x14)
#define USB_REQ_LOOPBACKDATAWRITE               (0x15)
#define USB_REQ_LOOPBACKDATAREAD                (0x16)
#define USB_REQ_SETINTERFACEDS                  (0x17)

/* USB feature values */

#define USB_FEATURE_ENDPOINTHALT                 0
#define USB_FEATURE_SELFPOWERED                  0
#define USB_FEATURE_REMOTEWAKEUP                 1
#define USB_FEATURE_TESTMODE                     2
#define USB_FEATURE_BATTERY                      2
#define USB_FEATURE_BHNPENABLE                   3
#define USB_FEATURE_WUSBDEVICE                   3
#define USB_FEATURE_AHNPSUPPORT                  4
#define USB_FEATURE_AALTHNPSUPPORT               5
#define USB_FEATURE_DEBUGMODE                    6

/* Generic descriptor header offsets */

#define USB_DESC_DESCLENOFFSET                   0
#define USB_DESC_DESCTYPEOFFSET                  1

/* Descriptor types */

#define USB_DESC_TYPE_DEVICE                    (0x01)
#define USB_DESC_TYPE_CONFIG                    (0x02)
#define USB_DESC_TYPE_STRING                    (0x03)
#define USB_DESC_TYPE_INTERFACE                 (0x04)
#define USB_DESC_TYPE_ENDPOINT                  (0x05)
#define USB_DESC_TYPE_DEVICEQUALIFIER           (0x06)
#define USB_DESC_TYPE_OTHERSPEEDCONFIG          (0x07)
#define USB_DESC_TYPE_INTERFACEPOWER            (0x08)
#define USB_DESC_TYPE_OTG                       (0x09)
#define USB_DESC_TYPE_DEBUG                     (0x0a)
#define USB_DESC_TYPE_INTERFACEASSOCIATION      (0x0b)
#define USB_DESC_TYPE_SECURITY                  (0x0c)
#define USB_DESC_TYPE_KEY                       (0x0d)
#define USB_DESC_TYPE_ENCRYPTION_TYPE           (0x0e)
#define USB_DESC_TYPE_BOS                       (0x0f)
#define USB_DESC_TYPE_DEVICECAPABILITY          (0x10)
#define USB_DESC_TYPE_WIRELESS_ENDPOINTCOMP     (0x11)
#define USB_DESC_TYPE_CSDEVICE                  (0x21)
#define USB_DESC_TYPE_CSCONFIG                  (0x22)
#define USB_DESC_TYPE_CSSTRING                  (0x23)
#define USB_DESC_TYPE_CSINTERFACE               (0x24)
#define USB_DESC_TYPE_CSENDPOINT                (0x25)

/* Device and interface descriptor class codes */

#define USB_CLASS_PER_INTERFACE                 (0x00)
#define USB_CLASS_AUDIO                         (0x01)
#define USB_CLASS_COMM                          (0x02)
#define USB_CLASS_HID                           (0x03)
#define USB_CLASS_PHYSICAL                      (0x05)
#define USB_CLASS_STILL_IMAGE                   (0x06)
#define USB_CLASS_PRINTER                       (0x07)
#define USB_CLASS_MASS_STORAGE                  (0x08)
#define USB_CLASS_HUB                           (0x09)
#define USB_CLASS_CDC_DATA                      (0x0a)
#define USB_CLASS_CSCID                         (0x0b)
#define USB_CLASS_CONTENT_SEC                   (0x0d)
#define USB_CLASS_VIDEO                         (0x0e)
#define USB_CLASS_WIRELESS_CONTROLLER           (0xe0)
#define USB_CLASS_APP_SPEC                      (0xfe)
#define USB_CLASS_VENDOR_SPEC                   (0xff)

/* Values for configuration descriptor attributes */

#define USB_CONFIG_ATTR_BATTERY                 (0x10) /* Battery powered */
#define USB_CONFIG_ATTR_WAKEUP                  (0x20) /* Remote wakeup */
#define USB_CONFIG_ATTR_SELFPOWER               (0x40) /* Self-powered */
#define USB_CONFIG_ATTR_ONE                     (0x80) /* Must be one */

/* Endpoint descriptor address */

#define USB_EP_ADDR_NUMBER_MASK                 (0x0f)
#define USB_EP_ADDR_DIR_MASK                    (0x80)

/* Endpoint descriptor attributes */

#define USB_EP_ATTR_XFERTYPE_MASK               (0x03)
#define USB_EP_ATTR_XFER_CONTROL                (0x00)
#define USB_EP_ATTR_XFER_ISOC                   (0x01)
#define USB_EP_ATTR_XFER_BULK                   (0x02)
#define USB_EP_ATTR_XFER_INT                    (0x03)
#define USB_EP_ATTR_MAX_ADJUSTABLE              (0x80)

/************************************************************************************
 * Public Types
 ************************************************************************************/

/* This structure is used to send control requests to a USB device. */

struct usb_ctrlreq_s
{
  uint8_t type;                /* Matches request type */
  uint8_t req;                 /* Matches request field */
  uint8_t value[2];
  uint8_t index[2];
  uint8_t len[2];
};
#define USB_SIZEOF_CTRLREQ 8

/* Generic descriptor */

struct usb_desc_s
{
  uint8_t len;               /* Descriptor length */
  uint8_t type;              /* Descriptor type */
};

/* Device descriptor */

struct usb_devdesc_s
{
  uint8_t len;               /* Descriptor length */
  uint8_t type;              /* Descriptor type */
  uint8_t usb[2];            /* USB version */
  uint8_t class;             /* Device class */
  uint8_t subclass;          /* Device sub-class */
  uint8_t protocol;          /* Device protocol */
  uint8_t mxpacketsize;      /* Max packet size (ep0) */
  uint8_t vender[2];         /* Vendor ID */
  uint8_t product[2];        /* Product ID */
  uint8_t device[2];         /* Device ID */
  uint8_t imfgr;             /* Manufacturer */
  uint8_t iproduct;          /* Product */
  uint8_t serno;             /* Serial number */
  uint8_t nconfigs;          /* Number of configurations */
};
#define USB_SIZEOF_DEVDESC 18

/* Configuration descriptor */

struct usb_cfgdesc_s
{
  uint8_t len;               /* Descriptor length */
  uint8_t type;              /* Descriptor type */
  uint8_t totallen[2];       /* Total length */
  uint8_t ninterfaces;       /* Number of interfaces */
  uint8_t cfgvalue;          /* Configuration value */
  uint8_t icfg;              /* Configuration */
  uint8_t attr;              /* Attributes */
  uint8_t mxpower;           /* Max power (mA/2) */
};
#define USB_SIZEOF_CFGDESC 9

struct usb_otherspeedconfigdesc_s
{
  uint8_t  len;               /* Descriptor length */
  uint8_t  type;              /* Descriptor type */
  uint8_t  totallen[2];       /* Total length */
  uint8_t  ninterfaces;       /* Number of interfaces */
  uint8_t  cfgvalue;          /* Configuration value */
  uint8_t  icfg;              /* Configuration */
  uint8_t  attr;              /* Attributes */
  uint8_t  mxpower;           /* Max power (mA/2) */
};
#define USB_SIZEOF_OTHERSPEEDCONFIGDESC 9

/* String descriptor */

struct usb_strdesc_s
{
  uint8_t len;               /* Descriptor length */
  uint8_t type;              /* Descriptor type */
  uint8_t data[2];
};

/* Interface descriptor */

struct usb_ifdesc_s
{
  uint8_t len;               /* Descriptor length */
  uint8_t type;              /* Descriptor type */
  uint8_t ifno;              /* Interface number */
  uint8_t alt;               /* Alternate setting */
  uint8_t neps;              /* Number of endpoints */
  uint8_t class;             /* Interface class */
  uint8_t subclass;          /* Interface sub-class */
  uint8_t protocol;          /* Interface protocol */
  uint8_t iif;               /* iInterface */
};
#define USB_SIZEOF_IFDESC 9

/* Endpoint descriptor */

struct usb_epdesc_s
{
  uint8_t  len;               /* Descriptor length */
  uint8_t  type;              /* Descriptor type */
  uint8_t  addr;              /* Endpoint address */
  uint8_t  attr;              /* Endpoint attributes */
  uint8_t  mxpacketsize[2];   /* Maximum packet size */
  uint8_t  interval;          /* Interval */
};
#define USB_SIZEOF_EPDESC 7

struct usb_audioepdesc_s
{
  struct usb_epdesc_s ep;
  uint8_t  refresh;
  uint8_t  synchaddr;
};
#define USB_SIZEOF_AUDIOEPDESC 9

/* Device qualifier descriptor */

struct usb_qualdesc_s
{
  uint8_t  len;               /* Descriptor length */
  uint8_t  type;              /* Descriptor type */
  uint8_t  usb[2];            /* USB version */
  uint8_t  class;             /* Qualifier class */
  uint8_t  subclass;          /* Qualifier sub-class */
  uint8_t  protocol;          /* Qualifier protocol */
  uint8_t  mxpacketsize;      /* Max packet size (ep0) */
  uint8_t  nconfigs;          /* Number of configurations */
  uint8_t  reserved;
};
#define USB_SIZEOF_QUALDESC 10

/************************************************************************************
 * Public Data
 ************************************************************************************/

/************************************************************************************
 * Public Functions
 ************************************************************************************/

#endif // __NUTTX_USB_USB_H
