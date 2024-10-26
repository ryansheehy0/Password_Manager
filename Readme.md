# Password Manager
A CLI password manger that uses a very secure and simple encryption algorithm.

## How it works
Imagine you had a combination lock, but instead of the dials being from 0-9, they are all the characters you can type on the keyboard (except for the tab key). Now, imagine that the lock doesn't have 4, but 64 different dials.

<img width=250 src="./combination_lock.jpeg">

If you wanted to store one of your passwords, like one for a website, you could dial it on this modified combination lock. However, if someone else came by they could see your password. This is like storing your passwords in a plain text document.

To solve this, you could remember 64 random characters, associate those characters with a number(0-94), and rotate each dial upwards by its respective number. This would effectively scramble the password, so someone who sees it won't know your password.

Of course, remembering 64 random characters is a little impractical. A better solution would be a black box function. If you could input a single master password, the black box could generate those same 64 random characters each time, based on the password. Change the master password, and the black box generates a new set of random characters.

Great. Now you can safely store one password. But what if you wanted to store more than one password? To do this, you could have multiple combination locks for each of your passwords and have each of them scrambled by the same 64 random characters.

But if an attacker happened to guess one of your passwords, they could reverse engineer the random 64 characters, and use that to unscrambled all of your other passwords. To prevent this, you could assign each lock an ID and use this ID as an additional input into your black box. This would create unique 64 random characters for each of your passwords, even with the same master password.

Suppose you also wanted to store other information, like a name for which website they belong to and a username, alongside each password. You could add two more locks per password, one for the account name and another for the username, each scrambled using the same 64 random characters.

But what if an attacker happened to guess your name or username. They could then reverse engineer the random 64 characters and get your password. To solve this, you can add another input into your black box. That being the field name (such as "name", "username", or "password"). This ensures each field generates a unique 64 random characters, so that knowing one field won't allow you to unscramble the others.

And that’s how this password manager works. Each password consists of an ID, field name, and field value. The black box is called a hash function. It takes in the ID, field name, and master password and gives you 64 random characters. Rotating upwards by the corresponding number is what I call simple encryption, and rotating downwards by the same number is called simple decryption.

### Visual overview
The hash uses 50 rounds of sha512 under the hood, so it's cryptographically secure.

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

### Simple Encryption/Decryption
