#include "bitvector.h"
int main()
{
	
	int fdes=_open("x.idx",O_RDONLY | O_BINARY);
//	int fdes=_open("x_test3.cmx",O_RDONLY | O_BINARY);
	int ofdes=_open("x_test3.cmx",O_WRONLY|O_BINARY|O_CREAT|O_TRUNC,_S_IREAD|_S_IWRITE);
//	int ofdes=_open("x_test2.cmx",O_WRONLY|O_BINARY|O_CREAT|O_TRUNC,_S_IREAD|_S_IWRITE);
	uint32_t* offset=NULL;
	char head[8];

	//read header
	_read(fdes,head,8);
	uint32_t len[2];
	
	//read length
	_read(fdes,len,8);
	offset=(uint32_t*)malloc(sizeof(uint32_t)*(len[1]+1));
	
	//read offset
	_read(fdes,offset,sizeof(uint32_t)*(len[1]+1));

	_write(ofdes,head,8);
	_write(ofdes,len,8);
	_write(ofdes,offset,(len[1]+1)*4);

	
	//read bitmap
	int i=0;
//	for(i=0;i<5;i++){

	ibis::array_t<ibis::bitvector::word_t>
                        a0(fdes, offset[i], offset[i+1]);
	ibis::bitvector* bv=new ibis::bitvector(a0);  //we only read one bitvector as test
	bv->sloppySize(len[0]);
	//bv->COMPAX2WAH();

//	(*bv).decompress_compax();
	//do some querry

	//bv->WAH2COMPAX();

	bv->write(ofdes); //need to be replaced by a for loop

//	}
	_close(fdes);
	_close(ofdes);
	return 0;
}