<font style="color:rgb(0, 0, 0)"><font face="Verdana, Arial, Helvetica, sans-serif">#ifndef DOT_MATRIX
#define DOT_MATRIX
 
typedef unsigned char uchar;
#define THROW(str) ;
 
#define BYTE_LEN 8
#define CHECK_VAR(i,j) if((i)<0||(j)<0||(i)>=height||(j)>=width)THROW("Index out of Bound")
#define POS(matrix,i,j) (*((matrix) + (i) * (width) + (j)))
#define POS_BIT_GET(matrix,i,j) (POS((matrix),(i),(j)/BYTE_LEN) & (1<<(BYTE_LEN-(j)%BYTE_LEN-1)))
#define POS_BIT_SET_TRUE(matrix,i,j) (POS((matrix),(i),(j)/BYTE_LEN) |= (1<<(BYTE_LEN-(j)%BYTE_LEN-1)))
#define POS_BIT_SET_FALSE(matrix,i,j) (POS((matrix),(i),(j)/BYTE_LEN) &= (0xFF ^ (1<<(BYTE_LEN-(j)%BYTE_LEN-1))))
#define POS_BIT_SET(m,i,j,b) ((b)!=0)?POS_BIT_SET_TRUE((m),(i),(j)):POS_BIT_SET_FALSE((m),(i),(j))
 
/**
 * Remember: This class will only use `matrix` but NOT DELETE it
 */
class DotMatrix {
public:
    DotMatrix(int w,int h,uchar *matrix, bool isNowClearMatrix=true):
            width(w),height(h),matrix(matrix){
        if(isNowClearMatrix)clearData();
    }
    DotMatrix(const DotMatrix &src){
        Serial.println("DotMatrix copy construction - please avoid");
        width = src.width;
        height = src.height;
        matrix = src.matrix;
    }
    ~DotMatrix(){}
 
    void clearData(){
        memset(matrix,0,width*height*1);
    }
 
    inline void set(int i,int j,uchar val){
        CHECK_VAR(i,j);
        POS(matrix,i,j) = val;
    }
 
    inline uchar get(int i,int j){
        CHECK_VAR(i,j);
        return POS(matrix,i,j);
    }
 
    inline void setBit(int i,int jBit, bool b){
        CHECK_VAR(i,jBit/8);
        POS_BIT_SET(matrix,i,jBit,b);
    }
 
    inline bool getBit(int i,int jBit){
        CHECK_VAR(i,jBit/8);
        return POS_BIT_GET(matrix,i,jBit);
    }
 
    void fillTo(DotMatrix &fillTo, int xOffset, int yOffset, int scale){
        this->fillTo(fillTo,xOffset,yOffset,scale,scale,0,0,width*BYTE_LEN,height);
    }
 
    /**
     * fill the rect [xSrcBeg,ySrcBeg,xSrcEnd,ySrcEnd] to `fillTo` by the `offset` and `scale`
     * @param The things by **bit**
     */
    void fillTo(DotMatrix &fillTo, int xOffset, int yOffset, int xScale, int yScale,
            int xSrcBeg, int ySrcBeg, int xSrcEnd, int ySrcEnd) {
        for(int i = ySrcBeg;i<ySrcEnd;++i){
            for(int j = xSrcBeg;j<xSrcEnd;++j){
                for(int ii=0;ii<yScale;++ii){
                    for(int jj=0;jj<xScale;++jj){
                        //VAR_DUMP_INLINE(i);VAR_DUMP_INLINE(j);VAR_DUMP_INLINE(ii);VAR_DUMP(jj);
                        fillTo.setBit(yOffset+(i-ySrcBeg)*yScale+ii, xOffset+(j-xSrcBeg)*xScale+jj, POS_BIT_GET(matrix,i,j));
                    }
                }
            }
        }
    }
 
    void print(){
        for(int i = 0;i<height;++i){
            for(int j = 0;j<width;++j){
                for(int k = 7;k>=0;--k){
                    Serial.print((get(i,j) & (1<<k))!=0);
                }
                Serial.print(" ");
            }
            Serial.println(" ");
        }
        Serial.flush();
    }
 
    int getWidth(){
        return width;
    }
 
    int getHeight(){
        return height;
    }
 
    uchar *getMatrix(){
        return matrix;
    }
private:
    int width,height;
    uchar *matrix;
private:
    friend class DisplayHelper;
};
#undef BYTE_LEN
#undef POS
#undef POS_BIT
 
#endif