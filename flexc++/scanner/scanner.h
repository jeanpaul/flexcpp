// Generated by Flexc++ V0.8.3 on Mon, 16 Jan 2012 21:44:26 +0100

#ifndef Scanner_H_INCLUDED_
#define Scanner_H_INCLUDED_

// $insert baseclass_h
#include "scannerbase.h"

#include <stack>

#include <bobcat/linearmap>

#include "../flextypes/flextypes.h"

class Scanner: public ScannerBase, private FlexTypes
{
    bool d_endOfInput = false;
    bool d_allowNullMatches = false;  // allow a null-matching RE
    bool d_inBlock;             // when in-block return ' ' on blanks
    bool d_inCharClass;         // in a char-class return sequences as
                                //  IDENTIFIERS, and multiple blanks as ' '
    bool d_acceptMulti;         // in pre, block and multi specs: return
                                // IDENTIFIER and DECIMAL as themselves,
                                // otherwise accept their first chars as CHAR

    std::string d_catchAll;     // the contents of the catch-all rule.
                                // Requested by the parser to create an 
                                // additional catch all rule (.|\n) which is 
                                // needed by LOP expressions
    std::string d_rawString;

    bool d_caseSensitive;

    FBB::LinearMap<std::string, std::string> d_nameExpansion;

    // declared below:
    // SCStack d_scStack;

    public:
        Scanner(std::string const &fname);

        // $insert lexFunctionDecl
        int lex();
        int pLex();     // calls/returns lex(), clears beginOfPattern

        using ScannerBase::accept;
        void newDefinition();       // new named regex, 'line' miniscanner
                                    
        void addDefinition(std::string const &spName, TextType textType);

        void blockEnds();
        void eolnDollar();
        void acceptMulti();
        void multiAsChar();
        void needCatchAll();

        void forceCaseSensitive();
        void setCaseSensitive();

        void ignoreWS();
        bool allowNullMatches();

        bool endOfInput() const;
        void atEndOfInput();

        std::string rawStringContents() const;

    private:
        int openCC(int token);
        int closeCC(int token = 0);

        int handle(int token) const;

        int handleCharAfterBlanks();
        bool handleEOLNcomment();
        bool handleStdComment();
        bool handleDquote();
        int handleOpenBracket();
        bool handleRawString();
        bool endOfRawString();
        
        int handleMulti(int token);

        void switchToINITIAL();

        using ScannerBase::push;

        void push(StartCondition__ sc); // push and revert to sc
        int popSc(int token = 0);   // revert to the pushed StartCondition,
                                    // returning 'token'

            // the start-condition stack can only be used from push and popSC
        class SCStack: private std::stack<StartCondition__> 
        {
            friend void Scanner::push(StartCondition__ sc);
            friend int Scanner::popSc(int token);
        } d_scStack;
    
        int inspectBlock();
        void maybeSwitchStream();
        bool popStream();           // hides ScannerBase::popStream from
                                    // lex.cc 
        void setLineTags(std::string const &filename) const;
        void pushNameExpansion();

        int lex__();
        int executeAction__(size_t ruleNr);

        void print();

        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts

        void postCode(PostEnum__);

        bool moreInput();
        bool secondSectionDelimiter();
        bool insertedCatchAll();
};

inline void Scanner::needCatchAll()
{
    d_catchAll = "\n"
                 ".|\\n  lop3__();\n";    
}

inline bool Scanner::endOfInput() const
{
    return d_endOfInput;
}

inline void Scanner::atEndOfInput()
{
    d_endOfInput = true;
}

inline void Scanner::forceCaseSensitive()
{
    d_caseSensitive = true;
}

inline void Scanner::acceptMulti()
{
    d_acceptMulti = true;
}

inline void Scanner::multiAsChar()
{
    d_acceptMulti = false;
}

inline void Scanner::blockEnds() 
{
    d_inBlock = false;
}

inline void Scanner::eolnDollar() 
{
    push("/\\n");
}

inline void Scanner::preCode() 
{
    // optionally replace by your own code
}

inline void Scanner::postCode(PostEnum__) 
{
    // optionally replace by your own code
}

// $insert inlineLexFunction
inline int Scanner::lex()
{
    return lex__();
}

inline void Scanner::print()
{
    print__();
}

inline void Scanner::ignoreWS()
{
    push(StartCondition__::optws);
}
    
#endif // Scanner_H_INCLUDED_

