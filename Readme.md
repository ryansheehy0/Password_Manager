# Password Manager
A CLI password manger that uses a very secure and simple encryption algorithm.

## How it works

Each password has an id field, name field, username field, and password field.

Encrypt

```
hash(id + fieldName + masterPassword) -> ---------------hash---------------
                                         ------------field text------------
                         simpleEncryption__________________________________
                                         ----------encrypted text----------
```

Decrypt

```
hash(id + fieldName + masterPassword) -> ---------------hash---------------
                                         ----------encrypted text----------
                         simpleDecryption__________________________________
                                         ------------field text------------
```

- The hash uses sha256
- why the arguments into the hash
	- id so that each password gets a different hash
	- fieldName so each field gets a different hash
	- masterPassword so that an attacker cannot guess the hash and decrypt the field text

## Simple Encryption/Decryption
