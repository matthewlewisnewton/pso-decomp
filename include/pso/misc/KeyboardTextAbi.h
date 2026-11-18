#ifndef PSO_MISC_KEYBOARDTEXTABI_H
#define PSO_MISC_KEYBOARDTEXTABI_H

// Historical export: receives embedded text-record storage, not a Soft window.
// The borrowed byte string is decoded into the record's existing u16 buffer.
// Complete record identity, capacity and storage aliasing remain qualified.
extern "C" void set_text_from_string__19TWindowKeyBoardSoftFPc(void *storage, char *text);

#endif
