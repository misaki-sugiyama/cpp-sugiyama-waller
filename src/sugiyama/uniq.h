// A simple macro to generate unique variable name
#pragma once

#define SUGIYAMA_CONCAT_NAME_2(name1, name2) name1##name2
#define SUGIYAMA_CONCAT_NAME(name1, name2) SUGIYAMA_CONCAT_NAME_2(name1, name2)
#define __UNIQLOCALNAME__ SUGIYAMA_CONCAT_NAME(S_U_G_I_Y_A_M_A__U_N_I_Q_U_E__L_O_C_A_L__I_D_E_N_T_I_F_I_E_R___, __LINE__)
