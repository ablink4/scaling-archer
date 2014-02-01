"""
    Author: ablink4
    Date: 30 Dec 2013
    Description: Daily programming challenge.  See:
        http://www.reddit.com/r/dailyprogrammer/comments/1e97ob/051313_challenge_125_easy_word_analytics/

        This program takes in a text whose location is read from the comomand line.  The text in the format
        is guaranteed to be well-formed ASCII text with UNIX-style line endings.  For this example, the
        text for the input was Lorem Ipsum generated from http://www.lipsum.com/

        The following information is printed for the input text:

        Number of words
        Number of letters
        Number of symbols (any non-letter and non-digit character, excluding white spaces)
        Top three most common words (you may count "small words", such as "it" or "the")
        Top three most common letters
        Most common first word of a paragraph (paragraph being defined as a block of text with an empty line above it) 
        Number of words only used once 
        All letters not used in the document  
"""

import string

def word_analytics():

    filename = raw_input("Enter the input text file with absolute file location:  ")
    file_ptr = open(filename, 'r')

    text = file_ptr.read()

    # calculate # words
    text_words = text.split()
    print str(len(text_words)) + " words"

    # keep list of letters for further analysis later
    letters = []
    
    # do not store symbols, we won't need them later
    symbol_cnt = 0

    # calculate # letters
    for char in text:
        if char.isalpha():
            letters.append(char)
        elif not char.isalnum() and not char.isspace():
            symbol_cnt = symbol_cnt + 1
        
    print str(len(letters)) + " letters"
    print str(symbol_cnt) + " symbols"

    """
    if the last char of the word is a symbol, remove it.
    intent is to strip any punctuation so that duplicate words can be recognized
    i.e. "word" and "word." should be equivalent.
    """
    stripped_words = []
    
    for word in text_words:
        if not word[len(word) - 1].isalnum() and not word[len(word) - 1].isspace():
            word = word[:len(word) - 1]
        stripped_words.append(word)

    word_dict = {}

    # pre-populate letter dictionary with all letters in alphabet with value 0
    letter_dict = dict.fromkeys(string.ascii_lowercase, 0)

    # go through word list, and add each item to a dictionary, and use the value
    # to count the occurrences of each word
    for word in stripped_words:
        word = word.lower()
        if word not in word_dict:
            word_dict[word] = 1
        else:
            word_dict[word] = word_dict[word] + 1

        # count all letters
        for letter in word:
            letter_dict[letter] = letter_dict[letter] + 1
        
    sorted_words = sorted(word_dict, key=word_dict.get, reverse=True)
    sorted_letters = sorted(letter_dict, key=letter_dict.get, reverse=True)

    print "Top three most common words: " + sorted_words[0] + ", " + sorted_words[1] + ", " + sorted_words[2]
    print "Top three most common letters: " + sorted_letters[0] + ", " + sorted_letters[1] + ", " + sorted_letters[2] 

    # split text into paragraphs, if there are any - paragraphs are defined as
    # blocks of text with a blank line above them - which corresponds to 2 newlines
    paragraphs = text.split('\n\n')
    if len(paragraphs) > 1:
        first_words = {}
        for paragraph in paragraphs:
            paragraph_words = paragraph.split()
            if paragraph_words[0] not in first_words:
                first_words[paragraph_words[0]] = 1
            else:
                first_words[paragraph_words[0]] = first_words[paragraph_words[0]] + 1

        sorted_first_words = sorted(first_words, key=first_words.get, reverse=True)
        print sorted_first_words[0] + " is the most common first word of all paragraphs"


    single_words = ""
    for word in word_dict:
        if word_dict[word] is 1:
            # formatting - separate each word with commas
            if(len(single_words) is 0):
                single_words = word
            else:
                single_words = single_words + ", " + word

    unused_letters = ""
    for letter in letter_dict:
        if letter_dict[letter] is 0:
            if(len(unused_letters) is 0):
                unused_letters = letter
            else:
                unused_letters = unused_letters + ", " + letter

    # do not print if there are no single words or unused letters, respectively
    if len(single_words) <> 0:
        print "Words used only once: " + single_words
    if len(unused_letters) <> 0:
        print "Letters not used in document: " + unused_letters

word_analytics()

