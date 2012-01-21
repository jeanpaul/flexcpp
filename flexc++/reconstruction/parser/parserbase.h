// Generated by Bisonc++ V2.09.04 on Sat, 21 Jan 2012 16:07:34 +0100

#ifndef ParserBase_h_included
#define ParserBase_h_included

#include <vector>
#include <iostream>

// $insert preincludes
#include "preinclude.h"
// $insert debugincludes
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>

namespace // anonymous
{
    struct PI__;
}


class ParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        EXCL_START_CONDITION = 257,
        INCL_START_CONDITION,
        SECTION_DELIMITER,
        BASECLASSHEADER,
        CLASSHEADER,
        CLASSNAME,
        DEBUG,
        DEBUG_STEPS,
        IMPLEMENTATIONHEADER,
        INPUTIMPLEMENTATION,
        INPUTINTERFACE,
        INTERACTIVE,
        LEXFUNCTIONNAME,
        LEXSOURCE,
        NAMESPACE,
        NOLINES,
        SKELETON_DIRECTORY,
        ERR,
        BLOCK,
        IDENTIFIER,
        EOF_PATTERN,
        STRING,
        DECIMAL,
        ESCAPE_SEQUENCE,
        CC_START,
        CC_NEGATED,
        PREDEFINED_CLASS,
        ORNL,
        CHAR,
        CC_PLUS,
        CC_MINUS,
    };

// $insert STYPE
typedef  std::string STYPE__;


    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;

        ParserBase();

// $insert debugdecl
        static std::ostringstream s_out__;

        std::string symbol__(int value) const;
        std::string stype__(char const *pre, STYPE__ const &semVal,
                            char const *post = "") const;
        static std::ostream &dflush__(std::ostream &out);
        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool ParserBase::debug() const
{
    return d_debug__;
}

inline void ParserBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void ParserBase::ABORT() const
{
    // $insert debug
    if (d_debug__)
        s_out__ <<  "ABORT(): Parsing unsuccessful" << "\n" << dflush__;
    throw PARSE_ABORT__;
}

inline void ParserBase::ACCEPT() const
{
    // $insert debug
    if (d_debug__)
        s_out__ <<  "ACCEPT(): Parsing successful" << "\n" << dflush__;
    throw PARSE_ACCEPT__;
}

inline void ParserBase::ERROR() const
{
    // $insert debug
    if (d_debug__)
        s_out__ <<  "ERROR(): Forced error condition" << "\n" << dflush__;
    throw UNEXPECTED_TOKEN__;
}


// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define Parser ParserBase


#endif


