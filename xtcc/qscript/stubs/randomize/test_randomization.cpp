#include "new_named_range-v2.h"
#include "utils.h"
int main()
{
NamedRangeGroup sub_group_1_lev_1("sub_group_1_lev_1",6);
sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 5", 5, 1);
sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 6", 6, 2);
sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 7", 7, 3);
sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 8", 8, 4);

NamedRangeGroup sub_group_3_lev_2("sub_group_3_lev_2",1);
sub_group_3_lev_2.AddStub( "sub_group_3_lev_2 9", 9, 1);
sub_group_3_lev_2.AddStub( "sub_group_3_lev_2 10", 10, 2);
sub_group_3_lev_2.AddStub( "sub_group_3_lev_2 11", 11, 3);

NamedRangeGroup sub_group_4_lev_2("sub_group_4_lev_2",2);
sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 12", 12, 1);
sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 13", 13, 2);
sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 14", 14, 3);
sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 15", 15, 4);

NamedRangeGroup sub_group_5_lev_2("sub_group_5_lev_2",3);
sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 16", 16, 1);
sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 17", 17, 2);
sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 18", 18, 3);
sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 19", 19, 4);

NamedRangeGroup sub_group_2_lev_1("sub_group_2_lev_1",7);
sub_group_2_lev_1.AddGroup(sub_group_3_lev_2,sub_group_3_lev_2.index_in_group);
sub_group_2_lev_1.AddGroup(sub_group_4_lev_2,sub_group_4_lev_2.index_in_group);
sub_group_2_lev_1.AddGroup(sub_group_5_lev_2,sub_group_5_lev_2.index_in_group);

NamedRangeGroup sub_group_6_lev_1("sub_group_6_lev_1",13);
sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 25", 25, 1);
sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 26", 26, 2);
sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 27", 27, 3);
sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 28", 28, 4);

NamedRangeGroup top_lev_group("top_lev_group",13);
top_lev_group.AddStub( "top_lev_group 0", 0, 1);
top_lev_group.AddStub( "top_lev_group 1", 1, 2);
top_lev_group.AddStub( "top_lev_group 2", 2, 3);
top_lev_group.AddStub( "top_lev_group 3", 3, 4);
top_lev_group.AddStub( "top_lev_group 4", 4, 5);
top_lev_group.AddGroup(sub_group_1_lev_1,sub_group_1_lev_1.index_in_group);
top_lev_group.AddGroup(sub_group_2_lev_1,sub_group_2_lev_1.index_in_group);
top_lev_group.AddStub( "top_lev_group 20", 20, 8);
top_lev_group.AddStub( "top_lev_group 21", 21, 9);
top_lev_group.AddStub( "top_lev_group 22", 22, 10);
top_lev_group.AddStub( "top_lev_group 23", 23, 11);
top_lev_group.AddStub( "top_lev_group 24", 24, 12);
top_lev_group.AddGroup(sub_group_6_lev_1,sub_group_6_lev_1.index_in_group);


top_lev_group.Vectorize(&top_lev_group, top_lev_group.stub_grp_vec);
top_lev_group.Randomize();
vector<stub_pair> flat_display_nr_after_rnd;
top_lev_group.VectorizePrint(1, &top_lev_group, flat_display_nr_after_rnd);
display_flat_named_range ("flat_display_nr_after_rnd", flat_display_nr_after_rnd);
}
