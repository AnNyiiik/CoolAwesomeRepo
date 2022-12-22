#ifndef LEXERCOMMENTS_LEXER_H
#define LEXERCOMMENTS_LEXER_H

#define COMMENT_SIZE 100
#define CHARACTER_SIZE 10

// Write all comments like /* smth */ from the input file to the output file.
int writeCommentsToFile(char const *outputFile, char const *inputFile);

#endif //LEXERCOMMENTS_LEXER_H
