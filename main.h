#ifndef __main_h_
#define __main_h_

#ifndef FORMATCHI
#define FORMATCHI 0
#endif

#ifndef FORMATNYC
#define FORMATNYC 0
#endif


#if FORMATNYC && FORMATCHI
#error "Both FORMATNYC and FORMATCHI cannot be set to 1 simultaneously."
#elif !FORMATNYC && !FORMATCHI
#error "At least one of FORMATNYC or FORMATCHI must be set to 1."
#endif

#if FORMATNYC
#define FORMAT_TICKETS_NYC \
    plateNumber, \
    issueDate, \
    infractionId, \
    fineAmount, \
    issuingAgency

enum NYC_TICKETS {
    FORMAT_TICKETS_NYC
};


#elif FORMATCHI
#define FORMAT_TICKETS_CHI \
    issueDate, \
    plateNumber, \
    issuingAgency, \
    infractionId, \
    fineAmount

enum CHI_TICKETS {
    FORMAT_TICKETS_CHI
};

#endif

#define FORMAT_INFRACTIONS \
    infractionIdA, \
    description

enum INFRACTIONS {
    FORMAT_INFRACTIONS
};

#define TICKETS_FILE 1
#define INFRACTIONS_FILE 2
#define DELIM ";"
#define READ "r"
#define WRITE "w"

#endif

