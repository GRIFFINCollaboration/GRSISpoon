variables = open('variables', 'w');
branches = open('branches', 'w');
point = open('point', 'w');
populate = open('populate', 'w');
test = open('test', 'w');

leaves = [
 	'fUniqueID',
 	'fBits',
 	'fName',
 	'fTitle',
 	'MidasTimeStamp',
 	'MidasId',
 	'TriggerId',
 	'FragmentId',
 	'TriggerBitPattern',
 	'DigitizerType',
 	'ODBType',
 	'ChannelName',
 	'ChannelNumber',
 	'ChannelRaw',
 	'Cfd',
 	'Led',
 	'TimeToTrig',
 	'Charge',
 	'ChargeCal',
 	'TimeStampLow',
 	'TimeStampHigh',
 	'TimeStampLive',
 	'TimeStampTR',
 	'TimeStampTA',
 	'SamplesFound',
 	'SlowRiseTime',
 	'PileUp',
 	'wavebuffer'
]

for i in range(0,28):
	variables.write(leaves[i]+'_st;\n');
	variables.write(leaves[i]+'_ct;\n');

	branches.write('  TBranch *'+leaves[i]+'_st_b = benchmarkTree->GetBranch("'+leaves[i]+'");\n');
	branches.write('  TBranch *'+leaves[i]+'_ct_b = contenderTree->GetBranch("'+leaves[i]+'");\n');

	point.write('  '+leaves[i]+'_st_b->SetAddress(&'+leaves[i]+'_st);\n');
	point.write('  '+leaves[i]+'_ct_b->SetAddress(&'+leaves[i]+'_ct);\n');

	populate.write('    '+leaves[i]+'_st_b->GetEntry(i);\n');
	populate.write('    '+leaves[i]+'_ct_b->GetEntry(i);\n');

	test.write('    if('+leaves[i]+'_st != '+leaves[i]+'_ct){\n');
	test.write('      cout << "'+leaves[i]+' mismatch at entry " << i << "; do not attempt pull request!" << endl;\n');
	test.write('      return;\n');
	test.write('    }\n\n');

