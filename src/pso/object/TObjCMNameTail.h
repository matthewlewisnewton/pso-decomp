s32 get_creation_pad(void) {
    return *(s32 *)((s8 *)&controller_physical_port_bank.value + (TChCrEffCtrlPl::get_clamped_player_index() * 4));
}
