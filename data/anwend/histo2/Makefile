all: inf_all period regel

clean: inf_clean
	rm -f period regel

period: ../filtersvd2/tsvd_p_1
	cp ../filtersvd2/tsvd_p_1 period
	echo "0\t-2900\n0\t1300" >> period

regel: ../filtersvd2/tsvd_r_3
	cp ../filtersvd2/tsvd_r_3 regel
	echo "0\t-3000\n0\t1000" >> regel

