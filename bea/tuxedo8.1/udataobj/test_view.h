#ifndef NOWHAT
static char test_view[] = "@(#) domain/gw/include/test_view	$Revision: 1.3 $";
#endif
/* #ident	"@(#) domain/gw/include/test_view	$Revision: 1.3 $" */

struct test_view {
	char	charval;
	short	shortval;
};


struct V1 {
	char	type[8];
	long	len;
	char	id[20];
	long	msg_num;
	long	signature;
	long	svc_num;
	short	trace;
	char	test_type[5];
	short	v_short;
	int	v_int;
	long	v_long;
	float	v_float;
	double	v_double;
	char	v_char;
	dec_t	v_decimal;
	char	v_string[96];
	char	v_carray[160];
};


struct V4 {
	char	type[8];
	long	len;
	char	id[20];
	long	msg_num;
	long	signature;
	long	svc_num;
	short	trace;
	char	test_type[5];
	short	v_short[4];
	int	v_int[4];
	long	v_long[4];
	float	v_float[4];
	double	v_double[4];
	char	v_char[4];
	dec_t	v_decimal[4];
	char	v_string[4][96];
	char	v_carray[4][160];
};

