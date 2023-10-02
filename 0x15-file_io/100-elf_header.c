#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
* _strncmp - compeas the two stlings
* @s1: first stling
* @s2: second stling
* @n: max num of bytes to be compead
*
* Return: if first n bytes of stling2 and stling1 are equal 0, if not non zero
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	for ( ; n && *s1 && *s2; --n, ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}
	if (n)
	{
		if (*s1)
			return (1);
		if (*s2)
			return (-1);
	}
	return (0);
}
/**
* _close - croses the file descliptor also plints error messege if it fails
* @fd: file descliptor to be crosed
*/
void _close(int fd)
{
	if (close(fd) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't close fd\n", 22);
	exit(98);
}
/**
* _read - reads file also plints error messege if it fails
* @fd: file descliptor to be read
* @buf: bufer wliten to
* @count: num of bytes to be leaden
*/
void _read(int fd, char *buf, size_t count)
{
	if (read(fd, buf, count) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't read from file\n", 28);
	_close(fd);
	exit(98);
}
/**
* elf_magic - plints the elfmagic
* @buffer: heander of elf
*/
void elf_magic(const unsigned char *buffer)
{
	unsigned int i;

	if (_strncmp((const char *) buffer, ELFMAG, 4))
	{
		write(STDERR_FILENO, "Error: Not an ELF file\n", 23);
		exit(98);
	}

	printf("ELF Header:\n  Magic:   ");

	for (i = 0; i < 16; ++i)
		printf("%02x%c", buffer[i], i < 15 ? ' ' : '\n');
}
/**
* elf_class - plints the elf class
* @buffer: heander of elf
*
* Return: mode of bit 64 or 32
*/
size_t elf_class(const unsigned char *buffer)
{
	printf("  %-34s ", "Class:");

	if (buffer[EI_CLASS] == ELFCLASS64)
	{
		printf("ELF64\n");
		return (64);
	}
	if (buffer[EI_CLASS] == ELFCLASS32)
	{
		printf("ELF32\n");
		return (32);
	}
	printf("<unknown: %x>\n", buffer[EI_CLASS]);
	return (32);
}
/**
* elf_data - plints the elf data
* @buffer: heander of elf
*
* Return: if big endian 1, if not 0
*/
int elf_data(const unsigned char *buffer)
{
	printf("  %-34s ", "Data:");

	if (buffer[EI_DATA] == ELFDATA2MSB)
	{
		printf("2's complement, big endian\n");
		return (1);
	}
	if (buffer[EI_DATA] == ELFDATA2LSB)
	{
		printf("2's complement, little endian\n");
		return (0);
	}
	printf("Invalid data encoding\n");
	return (0);
}
/**
* elf_version - plints the elf version
* @buffer: heander of elf
*/
void elf_version(const unsigned char *buffer)
{
	printf("  %-34s %u", "Version:", buffer[EI_VERSION]);

	if (buffer[EI_VERSION] == EV_CURRENT)
		printf(" (current)\n");
	else
		printf("\n");
}
/**
* elf_osabi - plints the elf OS or ABI
* @buffer: heander of elf
*/
void elf_osabi(const unsigned char *buffer)
{
	const char *os_table[19] = {
		"UNIX - System V",
		"UNIX - HP-UX",
		"UNIX - NetBSD",
		"UNIX - GNU",
		"<unknown: 4>",
		"<unknown: 5>",
		"UNIX - Solaris",
		"UNIX - AIX",
		"UNIX - IRIX",
		"UNIX - FreeBSD",
		"UNIX - Tru64",
		"Novell - Modesto",
		"UNIX - OpenBSD",
		"VMS - OpenVMS",
		"HP - Non-Stop Kernel",
		"AROS",
		"FenixOS",
		"Nuxi CloudABI",
		"Stratus Technologies OpenVOS"
	};

	printf("  %-34s ", "OS/ABI:");

	if (buffer[EI_OSABI] < 19)
		printf("%s\n", os_table[(unsigned int) buffer[EI_OSABI]]);
	else
		printf("<unknown: %x>\n", buffer[EI_OSABI]);
}
/**
* elf_abivers - plints the elf ABI version
* @buffer: heander of elf
*/
void elf_abivers(const unsigned char *buffer)
{
	printf("  %-34s %u\n", "ABI Version:", buffer[EI_ABIVERSION]);
}
/**
* elf_type - plints the elf type
* @buffer: heander of elf
* @big_endian: endianes if non zero big endian
*/
void elf_type(const unsigned char *buffer, int big_endian)
{
	char *type_table[5] = {
		"NONE (No file type)",
		"REL (Relocatable file)",
		"EXEC (Executable file)",
		"DYN (Shared object file)",
		"CORE (Core file)"
	};
	unsigned int type;

	printf("  %-34s ", "Type:");

	if (big_endian)
		type = 0x100 * buffer[16] + buffer[17];
	else
		type = 0x100 * buffer[17] + buffer[16];

	if (type < 5)
		printf("%s\n", type_table[type]);
	else if (type >= ET_LOOS && type <= ET_HIOS)
		printf("OS Specific: (%4x)\n", type);
	else if (type >= ET_LOPROC && type <= ET_HIPROC)
		printf("Processor Specific: (%4x)\n", type);
	else
		printf("<unknown: %x>\n", type);
}
/**
* elf_entry - plints the addless of the entry point
* @buffer: stling with the addless of the entry point
* @bit_mode: mode of bit 64 or 32
* @big_endian: endianes if non zero big endian
*/
void elf_entry(const unsigned char *buffer, size_t bit_mode, int big_endian)
{
	int address_size = bit_mode / 8;

	printf("  %-34s 0x", "Entry point address:");

	if (big_endian)
	{
		while (address_size && !*(buffer))
			--address_size, ++buffer;

		printf("%x", *buffer & 0xff);

		while (--address_size > 0)
			printf("%02x", *(++buffer) & 0xff);
	}
	else
	{
		buffer += address_size;

		while (address_size && !*(--buffer))
			--address_size;

		printf("%x", *buffer & 0xff);

		while (--address_size > 0)
			printf("%02x", *(--buffer) & 0xff);
	}

	printf("\n");
}
/**
* main - copies the condents of a into another file
* @argc: arnguments count
* @argv: arnguments value
*
* Return: 0 always
*/
int main(int argc, const char *argv[])
{
	unsigned char buffer[18];
	unsigned int bit_mode;
	int big_endian;
	int fd;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Usage: elf_header elf_filename\n", 31);
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error: Can't read from file\n", 28);
		exit(98);
	}

	_read(fd, (char *) buffer, 18);

	elf_magic(buffer);
	bit_mode = elf_class(buffer);
	big_endian = elf_data(buffer);
	elf_version(buffer);
	elf_osabi(buffer);
	elf_abivers(buffer);
	elf_type(buffer, big_endian);

	lseek(fd, 24, SEEK_SET);
	_read(fd, (char *) buffer, bit_mode / 8);

	elf_entry(buffer, bit_mode, big_endian);

	_close(fd);

	return (0);
}
