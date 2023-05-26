#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: The string to measure the length of
 *
 * Return: The length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strcmp - Compares two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: 0 if the strings are equal,
 *         a positive value if s1 > s2,
 *         a negative value if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a specific substring
 * @haystack: The string to search
 * @needle: The substring to find
 *
 * Return: If needle starts with haystack, returns the address of the next character
 *         in haystack. Otherwise, returns NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (ret);
}
