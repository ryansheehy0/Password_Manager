let readline = require("readline")
  .createInterface({
    input: process.stdin,
    output: process.stdout
  })

async function question(questionString){
  return new Promise(resolve => {
    readline.question(questionString, userInput => {
      resolve(userInput)
    })
  })
}

const fs = require("fs")

let file
let encryptOrDecrypt
let password

(async () => {
  file = fs.readFileSync(await question("Enter your input file: "), 'ascii')

  const input = await question("Enter 'e' to encrypt or 'd' to decrypt: ")
  if(input !== 'e' && input !== 'd'){
    throw new Error("Needs to be either 'e' or 'd'.")
  }
  encryptOrDecrypt = input

  password = await question("Enter password: ")

  for(let i=0, passwordI=0; i < file.length; i++, passwordI++){
    const char = file.charAt(i)

    if(char === '\t' || char === '\n'){
      process.stdout.write(char)
      passwordI--
      continue
    }

    let passwordCode = password.charCodeAt(passwordI % password.length)
    let fileCode = file.charCodeAt(i)

    passwordCode -= 32
    fileCode -= 32

    let newFileCode
    if(encryptOrDecrypt === 'e'){
      newFileCode = fileCode + passwordCode
    }else if(encryptOrDecrypt === 'd'){
      newFileCode = (fileCode - passwordCode) + (127 - 32)
    }

    newFileCode = newFileCode % (127 - 32)

    newFileCode += 32

    const newFileChar = String.fromCharCode(newFileCode)

    process.stdout.write(newFileChar)
  }

  readline.close()
})()