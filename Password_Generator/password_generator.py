import random

length_str = input('Enter length of password: ')
while not length_str.isdigit():
	length_str = input('Length has to be digits: ')
length = int(length_str)

symbols = ""
while not (symbols == 'y' or symbols == 'n'):
	symbols = input('Can the password contain special characters(y/n): ')

if symbols == 'n':
	digits = [i for i in range(48, 58)]
	uppercase_letters = [i for i in range(65, 91)]
	lowercase_letters = [i for i in range(97, 123)]

	allowed_chars = digits + uppercase_letters + lowercase_letters

password = ""
for i in range(length):
	if symbols == 'y':
		password += chr(random.randint(32, 126))
	else:
		password += chr(random.choice(allowed_chars))

print(password)
