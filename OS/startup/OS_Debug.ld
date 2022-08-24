/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2022
 * Generated linker script file for MK66FN2M0xxx18
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.5.1 [Build 7266] [2022-04-13] on 16 авг. 2022 г., 15:34:33
 */

GROUP (
  "libgcc.a"
  "libc_nano.a"
  "libstdc++_nano.a"
  "libm.a"
  "libcr_newlib_semihost.a"
  "crti.o"
  "crtn.o"
  "crtbegin.o"
  "crtend.o"
)


MEMORY
{
  boot_m_interrupts     (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00000400
  boot_m_flash_config   (RX)  : ORIGIN = 0x00000400, LENGTH = 0x00000010
  boot_m_header         (RX)  : ORIGIN = 0x00000410, LENGTH = 0x00000100
  boot_m_text           (RX)  : ORIGIN = 0x00000510, LENGTH = 0x00005AF0
  
  m_reserv_1            (RX)  : ORIGIN = 0x00006000, LENGTH = 0x00000800
  m_reserv_2		    (RX)  : ORIGIN = 0x00006800, LENGTH = 0x00000800
  
  os_m_header           (RX)  : ORIGIN = 0x00007000, LENGTH = 0x00000200 /*Хотел сделать 100, но почему то контроллер падает в хардфалт*/
  os_m_interrupts		(RX)  : ORIGIN = 0x00007200, LENGTH = 0x00000400
  os_m_flash_config     (RX)  : ORIGIN = 0x00007600, LENGTH = 0x00000010
  os_m_text             (RX)  : ORIGIN = 0x00007610, LENGTH = 0x000179F0
  
  
  ALG_HEADER          (RX)  : ORIGIN = 0x0001F000, LENGTH = 0x00000100
  ALG_TEXT            (RX)  : ORIGIN = 0x0001F100, LENGTH = 0x00020F00
  
  
  SRAM_UPPER (rwx) : ORIGIN = 0x20000000, LENGTH = 0x30000 /* 192K bytes (alias RAM) */  
  SRAM_LOWER (rwx) : ORIGIN = 0x1fff0000, LENGTH = 0x10000 /* 64K bytes (alias RAM2) */  
  FLEX_RAM (rwx) : ORIGIN = 0x14000000, LENGTH = 0x1000 /* 4K bytes (alias RAM3) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x200000 ; /* 2M bytes */  
  __top_Flash = 0x0 + 0x200000 ; /* 2M bytes */  
  __base_SRAM_UPPER = 0x20000000  ; /* SRAM_UPPER */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM_UPPER = 0x20000000 + 0x30000 ; /* 192K bytes */  
  __top_RAM = 0x20000000 + 0x30000 ; /* 192K bytes */  
  __base_SRAM_LOWER = 0x1fff0000  ; /* SRAM_LOWER */  
  __base_RAM2 = 0x1fff0000 ; /* RAM2 */  
  __top_SRAM_LOWER = 0x1fff0000 + 0x10000 ; /* 64K bytes */  
  __top_RAM2 = 0x1fff0000 + 0x10000 ; /* 64K bytes */  
  __base_FLEX_RAM = 0x14000000  ; /* FLEX_RAM */  
  __base_RAM3 = 0x14000000 ; /* RAM3 */  
  __top_FLEX_RAM = 0x14000000 + 0x1000 ; /* 4K bytes */  
  __top_RAM3 = 0x14000000 + 0x1000 ; /* 4K bytes */  



ENTRY(ResetISR)

SECTIONS
{
	
	.os_header :
	{  
	  . = ALIGN(4);
	  KEEP(*(.os_wrap_header))
	} > os_m_header 
	
	
	/* The startup code goes first into internal flash */
    .interrupts :
    {
		FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

    } > os_m_interrupts = 0xEE
	
	.flash_config : 
    {
		PROVIDE(__FLASH_CONFIG_START__ = .) ;
        KEEP(*(.FlashConfig))
        PROVIDE(__FLASH_CONFIG_END__ = .) ;
    } > os_m_flash_config = 0xEE
	
	
	
	 /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(8)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > os_m_text

    .ARM.exidx : ALIGN(8)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > os_m_text
	
	
     /* MAIN TEXT SECTION */
    .text : ALIGN(8)
    {
       FILL(0xff)
       *(.text*)
       KEEP(*freertos*/tasks.o(.rodata*)) /* FreeRTOS Debug Config */
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(8);
            /* C++ constructors etc */
            . = ALIGN(8);
            KEEP(*(.init))
            
            . = ALIGN(8);
            __preinit_array_start = .;
            KEEP (*(.preinit_array))
            __preinit_array_end = .;
            
            . = ALIGN(8);
            __init_array_start = .;
            KEEP (*(SORT(.init_array.*)))
            KEEP (*(.init_array))
            __init_array_end = .;
            
            KEEP(*(.fini));
            
            . = ALIGN(8);
            KEEP (*crtbegin.o(.ctors))
            KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
            KEEP (*(SORT(.ctors.*)))
            KEEP (*crtend.o(.ctors))
            
            . = ALIGN(8);
            KEEP (*crtbegin.o(.dtors))
            KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
            KEEP (*(SORT(.dtors.*)))
            KEEP (*crtend.o(.dtors))
            . = ALIGN(8);
            /* End C++ */
    } > os_m_text
 	OS_TEXT_END = .; 
    _etext = .;
        
 
    /* USB_RAM */
    .m_usb_data (NOLOAD) :
    {
        *(m_usb_bdt)
    } > SRAM_UPPER AT> SRAM_UPPER
    /* DATA section for SRAM_LOWER */

    /* MAIN DATA SECTION */
    .uninit_RESERVED (NOLOAD) : ALIGN(8)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(8) ;
        _end_uninit_RESERVED = .;
    } > SRAM_UPPER AT> SRAM_UPPER




    /* Main DATA section (SRAM_UPPER) */
    .data : ALIGN(8)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM = .) ;
       PROVIDE(__start_data_SRAM_UPPER = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
       *(.data*)
       . = ALIGN(8) ;
       _edata = . ;
       PROVIDE(__end_data_RAM = .) ;
       PROVIDE(__end_data_SRAM_UPPER = .) ;
    } > SRAM_UPPER AT>os_m_text
    
    OS_DATA_END = OS_TEXT_END + SIZEOF(.data);

    /* BSS section for SRAM_LOWER */
    .bss_RAM2 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_SRAM_LOWER = .) ;
       *(.bss.$RAM2)
       *(.bss.$SRAM_LOWER)
       *(.bss.$RAM2.*)
       *(.bss.$SRAM_LOWER.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_SRAM_LOWER = .) ;
    } > SRAM_LOWER AT> SRAM_LOWER

    /* BSS section for FLEX_RAM */
    .bss_RAM3 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       PROVIDE(__start_bss_FLEX_RAM = .) ;
       *(.bss.$RAM3)
       *(.bss.$FLEX_RAM)
       *(.bss.$RAM3.*)
       *(.bss.$FLEX_RAM.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
       PROVIDE(__end_bss_FLEX_RAM = .) ;
    } > FLEX_RAM AT> FLEX_RAM

    /* MAIN BSS SECTION */
    .bss : ALIGN(8)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM = .) ;
        PROVIDE(__start_bss_SRAM_UPPER = .) ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM = .) ;
        PROVIDE(__end_bss_SRAM_UPPER = .) ;
        PROVIDE(end = .);
    } > SRAM_UPPER AT> SRAM_UPPER

    /* NOINIT section for SRAM_LOWER */
    .noinit_RAM2 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_SRAM_LOWER = .) ;
       *(.noinit.$RAM2)
       *(.noinit.$SRAM_LOWER)
       *(.noinit.$RAM2.*)
       *(.noinit.$SRAM_LOWER.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_SRAM_LOWER = .) ;
    } > SRAM_LOWER AT> SRAM_LOWER

    /* NOINIT section for FLEX_RAM */
    .noinit_RAM3 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM3 = .) ;
       PROVIDE(__start_noinit_FLEX_RAM = .) ;
       *(.noinit.$RAM3)
       *(.noinit.$FLEX_RAM)
       *(.noinit.$RAM3.*)
       *(.noinit.$FLEX_RAM.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM3 = .) ;
       PROVIDE(__end_noinit_FLEX_RAM = .) ;
    } > FLEX_RAM AT> FLEX_RAM

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(8)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM = .) ;
        PROVIDE(__start_noinit_SRAM_UPPER = .) ;
        *(.noinit*)
         . = ALIGN(8) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM_UPPER = .) ;        
    } > SRAM_UPPER AT> SRAM_UPPER



    /* Reserve and place Heap within memory map */
    _HeapSize = 0x1000;
    .heap :  ALIGN(8)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(8);
        _pvHeapLimit = .;
    } > SRAM_UPPER

     _StackSize = 0x1000;
     /* Reserve space in memory for Stack */
    .heap2stackfill  :
    {
        . += _StackSize;
    } > SRAM_UPPER
    /* Locate actual Stack in memory map */
    .stack ORIGIN(SRAM_UPPER) + LENGTH(SRAM_UPPER) - _StackSize - 0:  ALIGN(8)
    {
        _vStackBase = .;
        . = ALIGN(8);
        _vStackTop = . + _StackSize;
    } > SRAM_UPPER

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
    
    
    
    __boot_os_start = ORIGIN(os_m_interrupts);
  	__boot_os_end = OS_DATA_END;
}