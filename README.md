# Text-to-Speech Program in C

This program allows users to perform several text-related operations such as writing text to a file, reading from a file, sorting text, printing text, converting text to speech (both live and WAV file generation), and managing text files with simple functionalities.

## Features
1. **Write Text to File**: Enter multiple lines of text, and store them in a text file.
2. **Read Text from File**: Load text data from an existing file into the program.
3. **Sort Text**: Sort the text lines in alphabetical order using the Bubble Sort algorithm.
4. **Print Text**: Display the stored text from the file or memory.
5. **Text-to-Speech (Live)**: Speak the loaded text aloud using the `espeak` program.
6. **Generate WAV File from Text**: Convert the text into a speech audio file in WAV format.
7. **Exit**: Exit the program.

## Prerequisites
Before running the program, make sure you have the following installed:
- `espeak` (for text-to-speech functionality)
- A C compiler (like `gcc`)

## Compilation and Execution
To compile and run the program, follow these steps:

1. Save the code in a file named `text_to_speech.c`.
2. Open a terminal and navigate to the directory containing `text_to_speech.c`.
3. Compile the code with `gcc`:
   ```bash
   gcc text_to_speech.c -o text_to_speech
   ```
4. Run the program:
   ```bash
   ./text_to_speech
   ```

## Program Flow

### 1. Write Text to File
You can input multiple lines of text, and they will be saved in a file. Type "STOP" to end the input.

### 2. Read Text from File
Read text from the `mytext.txt` file and store it in memory.

### 3. Sort Text (Bubble Sort)
Once text is read, you can sort it in alphabetical order using the Bubble Sort algorithm.

### 4. Print Text
Print all the text that has been loaded into memory.

### 5. Text-to-Speech (Live)
The program will read the text aloud in a language of your choice (English, Bulgarian, or Spanish). You can also adjust the pitch of the voice.

### 6. Generate WAV File from Text
Generate a `.wav` file with the speech of the loaded text. Choose the language and pitch, and a WAV file named `output.wav` will be created.

### 7. Exit
Exit the program.

## File Format
The text is stored in a plain text file (`mytext.txt`) with one line per piece of text. Each time you add new text, it appends to the file.

## Memory Management
The program dynamically allocates memory for storing text lines and ensures memory is freed before the program exits.

## Example Usage

```bash
-----------------------------------
 Text-to-Speech in C 
-------------------------------------
1) Write text to file
2) Read text from file
3) Sort text (Bubble Sort)
4) Print text
5) Text-to-Speech (live)
6) Generate WAV file from text
7) Exit
Choose an option: 1
Enter lines of text (type 'STOP' on a line to finish):
Hello World
STOP

-----------------------------------
 Text-to-Speech in C 
-------------------------------------
1) Write text to file
2) Read text from file
3) Sort text (Bubble Sort)
4) Print text
5) Text-to-Speech (live)
6) Generate WAV file from text
7) Exit
Choose an option: 2
Read 1 lines from mytext.txt

-----------------------------------
 Text-to-Speech in C 
-------------------------------------
1) Write text to file
2) Read text from file
3) Sort text (Bubble Sort)
4) Print text
5) Text-to-Speech (live)
6) Generate WAV file from text
7) Exit
Choose an option: 5
Select language:
1) English
2) Bulgarian
3) Spanish
Choose an option: 1
Enter pitch (0-99 recommended): 50
Speaking text live...
```

## Notes
- Ensure that `espeak` is installed and accessible in your system’s PATH for text-to-speech functionality.
- The maximum number of lines supported is `100`, and each line can have up to `256` characters.

## License
This program is open-source and free to use.
