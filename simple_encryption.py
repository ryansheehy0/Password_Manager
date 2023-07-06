import readline
import glob
import getpass

readline.parse_and_bind('tab: complete')
input_file = input('Enter your input file: ')

encrypt_or_decrypt = ""
while encrypt_or_decrypt not in ['e', 'd']:
    encrypt_or_decrypt = input("Enter 'e' to encrypt or 'd' to decrypt: ")

password = getpass.getpass(prompt='Enter password: ')

with open(input_file, 'r') as file: #open in read mode
    output_data = ""
    password_index = 0
    input_character = ""
    decimal_input_character = 0
    decimal_password_character = 0
    decimal_output_character = 0
    while True:
        #get next input character
            input_character = file.read(1)
            if not input_character:
                break
        #if the input character is a tab then write that to the output data and return
            if input_character == '\t' or input_character == '\n':
                output_data += input_character
                continue
        #get next password character
            password_character = password[password_index]
            password_index = (password_index + 1) % len(password)
        #get input character and password character as a decimal
            decimal_input_character = ord(input_character)
            decimal_password_character = ord(password_character)
        #subtract 32 form input character and password character
            decimal_input_character-=32
            decimal_password_character-=32
        #if encrypt then add numbers and then mod (127-32)
            if encrypt_or_decrypt == "e":
                decimal_output_character = decimal_input_character + decimal_password_character
                decimal_output_character = decimal_output_character % (127 - 32)
        #if decrypt then subtract numbers and 
            if encrypt_or_decrypt == "d":
                decimal_output_character = decimal_input_character - decimal_password_character
                decimal_output_character = decimal_output_character + (127 - 32)
                decimal_output_character = decimal_output_character % (127 - 32)
        #add 32
            decimal_output_character+=32
        #write to output data
            output_data+=chr(decimal_output_character)

print(output_data)