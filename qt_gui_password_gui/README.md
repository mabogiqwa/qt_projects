This Qt Graphical User Interface (GUI) program generates a username and an initial password based on the full name of the user. The program follows specific rules to ensure the validity of the username and password.

Rules for Generating a Valid Username:
The username consists of 5 characters.
The first character is in upper case, and the rest are in lower case.
The username is created by combining the first 4 characters of the surname with the first character of the first name.
If the surname has fewer than 4 characters, additional characters are taken from the first name.
If the combined surname and first name have fewer than 5 characters, 0s are appended to create the username.
Rules for Generating the Initial Password:
The initial password is created by randomly selecting 5 characters from the full name of the user.
No spaces are allowed in the username or password.
User Input:
User input is obtained using a QInputDialog.
The full name is expected as a single string where each word is separated using a space (e.g., "Mike William Owen").
Output:
The generated username and password are displayed using a QMessageBox.
No verification of the user input is performed.
Feel free to use and modify this program according to your needs. If you have any questions or suggestions, please let me know.

Note: This program assumes that the input follows the specified format, and no additional input validation is implemented.
