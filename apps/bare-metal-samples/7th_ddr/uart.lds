SECTIONS {
    . = 0x50000000;
    
	.text : {
			start.o
			* (.text)
	}

	.rodata : {
			* (.rodata)
	}

	.data : {
			* (.data)
	}

	. = ALIGN(4);
    __bss_start = .;
    .bss ALIGN(4)  : { *(.bss)  *(COMMON) }
    __bss_end = .;
}
