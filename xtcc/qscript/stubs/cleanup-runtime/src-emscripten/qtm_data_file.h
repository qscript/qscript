#ifndef QSCRIPT_QTM_FILE_H
#define QSCRIPT_QTM_FILE_H
#include <vector>
#include <fstream>
#include <utility>
#include "question.h"
#include "base_text.h"
#include "named_range.h"

namespace qtm_data_file_ns {



enum QtmFileMode
{
	READ_EQ_0 /* flat file */,
	READ_EQ_1 /* wrap around at 1000 i.e. 1001 to 1999 is in card 1,
			2001 to 2999 is in card 2 */ ,
	READ_EQ_2 /* wrap around at 100 i.e. 101 - 199 is in card 1
			201 to 299 is in card 2 */
};

struct QtmFileCharacteristics
{
	int cardDataStartAt_;
	int cardDataWrapAroundAt_;
	bool dontBreakQuestionsAtBoundary_;
	QtmFileMode qtmFileMode_;
	int currentCard_;
	int currentColumn_;
	int multiplier_;
	std::vector < pair<int,int> > maxColList_;
	//QtmFileCharacteristics();
	void NextCard();
	int GetCurrentColumnPosition();
	int UpdateCurrentColumn(int width_, AbstractRuntimeQuestion * q);
	QtmFileCharacteristics(int p_cardDataStartAt_,
			int p_cardWrapAroundAt,
			bool p_dontBreakQuestionsAtBoundary,
			QtmFileMode p_qtmFileMode);
	void Initialize();
};

struct Card
{
	std::vector<char> data_;
	std::vector<char> multiPunchData_;
	Card(int no_cols);
};

struct QtmDataFile
{
	std::vector<Card> cardVec_;
	QtmFileCharacteristics fileXcha_;
	void write_multi_code_data (int column,
			vector<int> & data,
			AbstractRuntimeQuestion * q);
	void write_single_code_data (int column, int width, int code, AbstractRuntimeQuestion *q);
	void write_record_to_disk(std::fstream & disk_file, int ser_no);
	bool CheckForValidColumnRef(int column);
	void AllocateCards();
	void Reset();
	void Initialize();
	// pair <card, col>
	std::pair<int, int> ConvertToCardColumn (int column);
	QtmDataFile();
};

struct CodeBucket
{
	std::vector<int> codeVec_;
	CodeBucket(): codeVec_()
	{ }
};

struct QtmDataDiskMap
{
public:
	AbstractRuntimeQuestion *q;
	int32_t startPosition_;
	int32_t width_;
	int32_t totalLength_;
	QtmDataFile & qtmDataFile_;
	//string baseText_;
	//bool dynamicBaseText_;
	//AbstractRuntimeQuestion * baseTextQuestion_;
	BaseText baseText_;
	QtmDataDiskMap(AbstractRuntimeQuestion * p_q,
		QtmDataFile & p_qtm_data_file, BaseText base_text);
	int GetTotalLength() { return totalLength_; }
	void write_data ();
	void write_single_code_data();
	void write_multi_code_data();
	void print_run(string jno);
	void print_map(std::fstream & map_file);
	void print_qax(std::fstream & qax_file, std::string setup_dir);
	void print_qin(std::string setup_dir);
	std::vector <CodeBucket> codeBucketVec_;
	void AllocateCards();
	void Reset();
private:
	QtmDataDiskMap& operator= (const QtmDataDiskMap&);
	QtmDataDiskMap(const QtmDataDiskMap&);
};

void init_exceptions();
char check_for_exceptions( vector <int> & data);
extern std::fstream qtm_data_file_writer_log;
// this function should be called first to initialise the
// log writer file
void init();


} /* close namespace qtm_data_file */

#endif /* QSCRIPT_QTM_FILE_H */
