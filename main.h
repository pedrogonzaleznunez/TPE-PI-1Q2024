#ifndef __main_h_
#define __main_h_

#ifndef FORMATNYC
#define FORMATNYC 0
#endif

#ifndef FORMATCHI
#define FORMATCHI 0
#endif

#if FORMATNYC
#define FORMAT_TICKETS_NYC \
    plate, \
    issueDate, \
    infractionId, \
    fineAmount, \
    issuingAgency

#define FORMAT_INFRACTIONS_NYC \
    infractionId, \
    description

enum NYC_TICKETS {
    FORMAT_TICKETS_NYC
};

enum NYC_INFRACTIONS {
    FORMAT_INFRACTIONS_NYC
};

#elif FORMATCHI
#define FORMAT_TICKETS_CHI \
    issueDate, \
    plate, \
    issuingAgency, \
    infractionId, \
    fineAmount

#define FORMAT_INFRACTIONS_CHI \
    infractionId, \
    description

enum CHI_TICKETS {
    FORMAT_TICKETS_CHI
};

enum CHI_INFRACTIONS {
    FORMAT_INFRACTIONS_CHI
};

#endif

#define TICKETS_FILE 1
#define INFRACTIONS_FILE 2
#define DELIM ";"

#endif

