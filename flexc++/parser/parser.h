// Generated by Bisonc++ V2.09.04 on Mon, 16 Jan 2012 21:40:37 +0100

#ifndef Parser_h_included
#define Parser_h_included

#include <string>

#include "../state/state.h"
#include "../block/block.h"

#include <bobcat/arg>

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"

namespace FBB
{
    class Arg;
}

class Options;
class States;
class Rules;

#undef Parser
class Parser: public ParserBase
{
    FBB::Arg &d_arg;

    // $insert scannerobject
    Scanner d_scanner;
    std::string const &d_matched;   // text matched at the last lex() call.
    Block   d_block;

    Options &d_options;

    bool d_boln;                    // rule starts at boln
    bool d_doError;                 // use the error() function at ERRORs
    bool d_printTokens;
    bool d_usesLOP;
    bool d_warnCarets;              // carets in a RE
    bool d_warnDollars;             // dollars in a RE
    size_t d_parentheses;
    size_t d_tokenCount;
    std::string d_expect;

    Rules &d_rules;
    States &d_states;

    static int s_ignoreToken;
    static std::string s_lastMsg;

    public:
        Parser(Rules &rules, States &states);
        int parse();

    private:
        Pattern eolnDollar();
        void orAction();
        void reset();       // prepare the parser for a new regex 
                            // (resetting tokencount and warning flags)

        Pattern boln();
        Pattern dollar();
        Pattern eofPattern();                               // .ih
        Pattern quotes();
        Pattern concatenate(Pattern const &lhs, Pattern const &rhs); // .ih
        Pattern lookahead(Pattern const &left, Pattern const &right);
        Pattern interval(Pattern const &regex, Interval const &interval);


        void assignBlock();                                 // .ih
        void noActions();                                   // .ih
        Pattern alternatives(Pattern const &lhs, 
                                Pattern const &rhs);     // .ih
        Pattern characterClass(CharClass const &charClass);   // .ih
        Pattern dot();                                   // .ih
        Pattern escape();                                // .ih
        Pattern str();                                   // .ih
        Pattern rawText();                               // .ih
        Pattern rawText(std::string const &str);         // .ih
        Pattern quantifier(Pattern const &regex);     // .ih

        void addRule(Pattern const &rule, bool resetMs = false);
        void addBlockRule(Pattern const &rule);

        void setFlags(size_t idx, State::Flag flag);    // called fm lookahead

        void block();
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();  

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
};

#endif





