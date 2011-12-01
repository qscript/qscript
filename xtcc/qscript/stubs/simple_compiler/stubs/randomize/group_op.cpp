#include "new_named_range.h"

int main()
{


	NamedRangeGroup grp_1("grp_1");
	grp_1.AddStub( " Kalyanam (Ratia Marg, Snagam Vihar, New Delhi)", 7, 1);
	grp_1.AddStub( " CASP Plan Project (Neem Chowk, Sangam Vihar, New Delhi)", 8, 2);
	grp_1.AddStub( " EFRAH (Aali Vihar, nr. Aali Village, New Delhi)", 9, 3);
	grp_1.AddStub( " Nav Srishti (Village neb Sarai, New Delhi)", 10, 4);

	NamedRangeGroup grp_21("grp_21");
	grp_21.AddStub( " Shape India (R/o block 5c, Sarai Kale Khan, DDA flat)", 13, 1);
	grp_21.AddStub( " Jai Jawan Jai Kisan trust (Cenquin) (Centre for community and child development, Jamia Milia Islamia)", 14, 2);

	NamedRangeGroup grp_22("grp_22");
	grp_22.AddStub( " Adarshila (Greater Kailash 2, New Delhi)", 15, 1);
	grp_22.AddStub( " Katha (A/3 Sarvodaya Enclave, New Delhi)", 16, 2);

	NamedRangeGroup grp_2("grp_2");
	grp_2.AddGroup(grp_21);
	grp_2.AddGroup(grp_22);

	NamedRangeGroup suvidha_kendra("suvidha_kendra");
	suvidha_kendra.AddStub( " CASP (JJ Colony, Madanpur Khadar, New Delhi)", 1, 1);
	suvidha_kendra.AddStub( " Prayatn (Basti Vikas Kendra, Jeevan Jyoti Rajiv Camp, D Block, Okhla PII", 2, 2);
	suvidha_kendra.AddStub( " Jal Shankar Memorial Centre (Jasloa Village, New Delhi) Jal", 3, 3);
	suvidha_kendra.AddStub( " Sakaar Outreach (Tanki Road, Meethapur Badarpur, New Delhi)", 4, 4);
	suvidha_kendra.AddStub( " Mamta health Institute for Mother and Child (JJ Camp, Tigri, New Delhi)", 5, 5);
	suvidha_kendra.AddStub( " New opportunities for Women (NOW) (Nr Shalimar Conema, New park)", 6, 6);
	suvidha_kendra.AddGroup(grp_1);
	suvidha_kendra.AddStub( " Navjyoti Development Society (Tekhand village, Okhla phase I, New Del)", 11, 8);
	suvidha_kendra.AddStub( " Sakaar Outreach (Madangir Ambedkar Nagar, New Delhi)", 12, 9);
	suvidha_kendra.AddGroup(grp_2);
	suvidha_kendra.AddStub( " Kalyanam (41/1407 DDA flats, Madangir, New Delhi)", 17, 11);

	suvidha_kendra.Vectorize(suvidha_kendra.stub_grp_vec);
	for (int i=0; i < suvidha_kendra.stub_grp_vec.size(); ++i) {
		suvidha_kendra.stub_grp_vec[i]->VectorizePrint();
	}


}
