.code16 #use 16-bit assembly
.globl _start #This tells us the linker where we want to start executing

_start:
	movw $message, %si	# load the offset of our message into si
	movb $0x00, %ah		# 0x00 - set video mode
	movb $0x03, %al 	# 0x03 - 80x25 text mode
    int $0x10			# call into the BIOS
	call fun

print_char:
	lodsb			# loads a single byte from [si] into al and increments si
	testb %al,%al   # checks to see if the byte is 0
	jz done			# if so, jump out (jz jumps if the ZF in EFLAGS is set)
	movb $0x0E,%ah  # 0x0E is the BIOS code to print the single character
	int $0x10		# call into the BIOS using a software interrupt
	jmp print_char	# go back to the start of the loop

done:
	jmp done		# loop forever

fun:
	movb $0x2A, %dl #put 0x04 in %dl
	ret

# The .string commnad inserts an ASCII string with a null terminator
message:
	.string	"Hello world"

# This pads out the rest of the 512 byte sector and then
# puts the magic 0x55AA that the BIOS expects at the end
.fill 510 - (. - _start), 1, 0

# Now we can put our magic bytes:
.byte 0x55
.byte 0xAA
