

TTigFragment *frag= 0;
int x = 0;


SetUpRoot()	{
	printf("FragmentTree->GetEntries() = %i\n",FragmentTree->GetEntries());
	FragmentTree->SetBranchAddress("TTigFragment",&frag);
	return;
}
