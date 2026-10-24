/* Keep the static embedded engine independent of System4/libsys4 symbols. */
#pragma once
#define bgi_read xsystem35_bgi_read
#define effect_init xsystem35_effect_init
#define mixer_init xsystem35_mixer_init
#define msgq_dequeue xsystem35_msgq_dequeue
#define msgq_dequeue_timeout xsystem35_msgq_dequeue_timeout
#define msgq_enqueue xsystem35_msgq_enqueue
#define msgq_free xsystem35_msgq_free
#define msgq_new xsystem35_msgq_new
#define wai_load xsystem35_wai_load
#define cg_load xsystem35_cg_load
#define mkdir_p xsystem35_mkdir_p
#define qnt_checkfmt xsystem35_qnt_checkfmt
#define qnt_extract xsystem35_qnt_extract
#define s2u xsystem35_s2u
#define sjis2utf xsystem35_sjis2utf
#define sjis_has_hankaku xsystem35_sjis_has_hankaku
#define sjis_has_zenkaku xsystem35_sjis_has_zenkaku
#define sys_error xsystem35_sys_error
#define sys_exit xsystem35_sys_exit
#define sys_message xsystem35_sys_message
#define utf2sjis xsystem35_utf2sjis
#define webp_checkfmt xsystem35_webp_checkfmt
#define webp_extract xsystem35_webp_extract
