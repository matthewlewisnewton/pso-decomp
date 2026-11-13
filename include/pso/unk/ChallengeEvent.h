#ifndef PSO_UNK_CHALLENGEEVENT_H
#define PSO_UNK_CHALLENGEEVENT_H

// Challenge-mode event records the TLobby event-set loader reads.
struct ChallengeEventHeader {
    void swap_endian();
};

struct ChallengeRandomEvent {
    void swap_endian();
};

struct ChallengeEventCommand {
    void append() const;
};

#endif
