#ifndef HARDDISK_PIO_MODE_HEADER
#define HARDDISK_PIO_MODE_HEADER

#include <stdint.h>

// This OS currently use LBA 48bit for handling hard disks.

// Ports

//! Primary bus I/O port.
/*! Used to transfer data with drives on primary bus*/
#define harddisk_primary_bus_io_port 0x1F0

//! Primary bus control port.
/*! Used to transfer control informations with drives on primary bus*/
#define harddisk_primary_bus_control_port 0x3F6

//! Secondary bus I/O port.
/*! Used to transfer data with drives on secondary bus*/
#define harddisk_secondary_bus_io_port 0x170

//! Secondary bus control port.
/*! Used to transfer control informations with drives on secondary bus*/
#define harddisk_secondary_bus_control_port 0x376

// Registers offsets

//! Offset of I/O based Data Register.
/*! Read/Write PIO data bytes. Offset for I/O base port.
Direction: read/write
Param. size for LBA48: 16 bit*/
#define harddisk_io_data_register_offset 0

//! Offset of I/O based Error Register.
/*! Used to retrieve any error generated by the last ATA command executed. Offset for I/O base port.
Direction: read
Param. size for LBA48: 16 bit*/
#define harddisk_io_io_error_register_offset 1

//! Offset of I/O based Features Register.
/*! Used to control command specific interface features. Offset for I/O base port.
Direction: write
Param. size for LBA48: 16 bit*/
#define harddisk_features_register_offset 1

//! Offset of I/O based Sector Count Register.
/*! Number of sectors to read/write (0 is a special value). Offset for I/O base port.
Direction: read/write
Param. size for LBA48: 16 bit*/
#define harddisk_io_sector_count_register_offset 2

//! Offset of I/O based Sector Number Register (LBAlo).
/*! This is CHS / LBA28 / LBA48 specific. Offset for I/O base port.
Direction: read/write
Param. size for LBA48: 16 bit*/
#define harddisk_io_sector_number_register_offset 3

//! Offset of I/O based Cylinder Low Register / (LBAmid).
/*! Partial Disk Sector address. Offset for I/O base port.
Direction: read/write
Param. size for LBA48: 16 bit*/
#define harddisk_io_cylinder_low_register_offset 4

//! Offset of I/O based Cylinder High Register / (LBAhi).
/*! Partial Disk Sector address. Offset for I/O base port.
Direction: read/write
Param. size for LBA48: 16 bit*/
#define harddisk_io_cylinder_high_register_offset 5

//! Offset of I/O based Drive / Head Register.
/*! Used to select a drive and/or head. Supports extra address/flag bits. Offset for I/O base port.
Direction: read/write
Param. size for LBA48: 8 bit*/
#define harddisk_io_drive_head_register_offset 6

//! Offset of I/O based Status Register.
/*! Used to read the current status. Offset for I/O base port.
Direction: read
Param. size for LBA48: 8 bit*/
#define harddisk_io_status_register_offset 7

//! Offset of I/O based Command Register.
/*! Used to send ATA commands to the device. Offset for I/O base port.
Direction: write
Param. size for LBA48: 8 bit*/
#define harddisk_io_command_register_offset 7

//! Offset of Control based Alternate Status Register.
/*! A duplicate of the Status Register from I/O port, which does not affect interrupts. Offset for Control base port.
Direction: read
Param. size for LBA48: 8 bit*/
#define harddisk_control_alterante_status_register_offset 0

//! Offset of Control based Device Control Register.
/*! Used to reset the bus or enable/disable interrupts. Offset for Control base port.
Direction: write
Param. size for LBA48: 8 bit*/
#define harddisk_control_device_control_register_offset 0

//! Offset of Control based Drive Address Register.
/*! Provides drive select and head select information. Offset for Control base port.
Direction: read
Param. size for LBA48: 8 bit*/
#define harddisk_control_drive_adderss_register_offset 1

// Structs

//! Hard disk I/O based Error Register.
/*! Struct used to read from Error Register of I/O port. Used to retrieve any error generated by the last ATA command executed.*/
typedef struct harddisk_io_error_register_fields
{
    //! Bad Block detected (short: BBK).
    uint8_t bad_block_detected : 1;
    //! Uncorrectable data error (short: UNC).
    uint8_t uncorrectable_data_error : 1;
    //! Media changed (short: MC).
    uint8_t media_changed : 1;
    //! ID not found (short: IDNF).
    uint8_t id_not_found : 1;
    //! Media change request (short: MCR).
    uint8_t media_change_request : 1;
    //! Aborted command (short: ABRT).
    uint8_t aborted_command : 1;
    //! Track zero not found (short: TKZNF).
    uint8_t track_zero_not_found : 1;
    //! Address mark not found (short: AMNF).
    uint8_t address_mark_not_found : 1;
    //! Unused.
    uint8_t unused;
} harddisk_io_error_register_fields;

//! Hard disk I/O based Error Register.
/*! Struct used to read from Error Register of I/O port. Used to retrieve any error generated by the last ATA command executed.*/
typedef union harddisk_io_error_register
{
    //! Fields of this union.
    harddisk_io_error_register_fields fields;
    //! Value of this union.
    uint16_t value;
} harddisk_io_error_register;

//! Hard disk I/O based Drive / Head Register.
/*! Struct used to read from Drive / Head Register of I/O port. Used to select a drive and/or head. Supports extra address/flag bits. */
typedef struct harddisk_io_drive_head_register_fields
{
    //! Always set.
    uint8_t always_set_field_2 : 1;
    //! Uses CHS addressing if clear or LBA addressing if set (short: LBA).
    uint8_t uses_lba : 1;
    //! Always set.
    uint8_t always_set_field_1 : 1;
    //! Selects the drive number (short: DRV).
    uint8_t drive_number : 1;
    //! In CHS addressing, bits 0 to 3 of the head. In LBA addressing, bits 24 to 27 of the block number.
    uint8_t chs_head_lba_block_number : 4;
} harddisk_io_drive_head_register_fields;

//! Hard disk I/O based Drive / Head Register.
/*! Struct used to read from Drive / Head Register of I/O port. Used to select a drive and/or head. Supports extra address/flag bits. */
typedef union harddisk_io_drive_head_register
{
    //! Fields of this union.
    harddisk_io_drive_head_register_fields fields;
    //! Value of this union.
    uint8_t value;

} harddisk_io_drive_head_register;

//! Hard disk I/O or Control based Status Register.
/*! Struct used to read from Status Register of I/O or Control port. Used to select a drive and/or head. Supports extra address/flag bits.
Technically, when BSY is set, the other bits in the Status byte are meaningless.
It is also generally a Bad Idea to test the "Seek Complete" (DSC) bit, because it has been deprecated and replaced by the newer SRV bit.
Reading the Device Control Register port gets you the value of the Alternate Status Register, instead.
The value of Alternate Status is always the same as the Regular Status port, but reading the Alternate Status port does not affect interrupts.*/
typedef struct harddisk_io_control_status_register_fields
{
    //! Indicates the drive is preparing to send/receive data (wait for it to clear). In case of 'hang' (it never clears), do a software reset. (short: BSY).
    uint8_t busy : 1;
    //! Bit is clear when drive is spun down, or after an error. Set otherwise. (short: RDY).
    uint8_t ready : 1;
    //! Drive Fault Error (does not set ERR). (short: DF).
    uint8_t drive_fault_error : 1;
    //! Overlapped Mode Service Request. (short: SRV).
    uint8_t overlapped_mode_service_request : 1;
    //! Set when the drive has PIO data to transfer, or is ready to accept PIO data. (short: DRQ).
    uint8_t has_pio_data_to_transfer_or_ready_to_accept_pio_data : 1;
    //! Corrected data. Always set to zero. (short: CORR).
    uint8_t corrected_data : 1;
    //! Index. Always set to zero.  (short: IDX).
    uint8_t index : 1;
    //! Indicates an error occurred. Send a new command to clear it (or nuke it with a Software Reset).  (short: ERR).
    uint8_t error_occurred : 1;
 
} harddisk_io_control_status_register_fields;

//! Hard disk I/O or Control based Status Register.
/*! Struct used to read from Status Register of I/O or Control port. Used to select a drive and/or head. Supports extra address/flag bits.
Technically, when BSY is set, the other bits in the Status byte are meaningless.
It is also generally a Bad Idea to test the "Seek Complete" (DSC) bit, because it has been deprecated and replaced by the newer SRV bit.
Reading the Device Control Register port gets you the value of the Alternate Status Register, instead.
The value of Alternate Status is always the same as the Regular Status port, but reading the Alternate Status port does not affect interrupts.*/
typedef union harddisk_io_control_status_register
{
    //! Fields of this union.
    harddisk_io_control_status_register_fields fields;
    //! Value of this union.
    uint8_t value;
} harddisk_io_control_status_register;

//! Hard disk Control based Device Control Register.
/*! Struct used to read from Device Control Register of Control port. Used to reset the bus or enable/disable interrupts.
There is an additional IO port that changes the behavior of each ATA bus, called the Device Control Register.
Each ATA bus has its own Control Register.
All other bits are reserved and should always be clear. In general, you will want to leave HOB, SRST, and nIEN cleared.
Set each Device Control Register to 0 once, during boot.*/
typedef struct harddisk_control_device_control_register_fields
{
    //! Set this to read back the High Order Byte of the last LBA48 value sent to an IO port (short: HOB).
    uint8_t high_order_byte_read : 1;
    //! Reserved, set to zero.
    uint8_t reserved_field_1 : 1;
    //! Reserved, set to zero.
    uint8_t reserved_field_2 : 1;
    //! Reserved, set to zero.
    uint8_t reserved_field_3 : 1;
    //! Reserved, set to zero.
    uint8_t reserved_field_4 : 1;
    //! Set, then clear (after 5us), this to do a "Software Reset" on all ATA drives on a bus, if one is misbehaving (short: SRST).
    uint8_t software_reset : 1;
    //! Set this to stop the current device from sending interrupts (short: nIEN).
    uint8_t stop_sending_interrupts : 1;
    //! Always set to zero.
    uint8_t always_clear_field_1 : 1;

} harddisk_control_device_control_register_fields;

//! Hard disk Control based Device Control Register.
/*! Struct used to read from Device Control Register of Control port. Used to reset the bus or enable/disable interrupts.
There is an additional IO port that changes the behavior of each ATA bus, called the Device Control Register.
Each ATA bus has its own Control Register.
All other bits are reserved and should always be clear. In general, you will want to leave HOB, SRST, and nIEN cleared.
Set each Device Control Register to 0 once, during boot.*/
typedef union harddisk_control_device_control_register
{
    //! Fields of this union.
    harddisk_control_device_control_register_fields fields;
    //! Value of this union.
    uint8_t value;
} harddisk_control_device_control_register;

//! Hard disk Control based Drive Address Register.
/*! Struct used to read from Drive Address Register of Control port. Provides drive select and head select information.*/
typedef struct harddisk_control_drive_address_register_fields
{
    //! Reserved for compatibility with floppy drive controllers which may use this bit.
    uint8_t reserved_for_floppy_controllers : 1;
    //! Write gate; goes low while writing to the drive is in progress (short: WTG).
    uint8_t write_gate : 1;
    //! One's compliment representation of the currently selected head (short: HS0 - HS3).
    uint8_t selected_head : 1;
    //! Drive 1 select. Clears when drive 1 selected (short: DS1).
    uint8_t select_drive_1 : 1;
    //! Drive 0 select. Clears when drive 0 selected (short: DS0).
    uint8_t select_drive_0 : 1;  
} harddisk_control_drive_address_register_fields;

//! Hard disk Control based Drive Address Register.
/*! Struct used to read from Drive Address Register of Control port. Provides drive select and head select information.*/
typedef union harddisk_control_drive_address_register
{
    //! Fields of this union.
    harddisk_control_drive_address_register_fields fields;
    //! Value of this union.
    uint8_t value;
} harddisk_control_drive_address_register;

#endif