#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#include <bitset>
#include <stdint.h>

using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */




bool readHead ( uint16_t head[8],    uint16_t& height, uint16_t& width,
                uint16_t& endian,    uint16_t& form,   uint16_t& channels,   uint16_t& bitsForChannel)
{
    endian = (head[0] << 8) + head[1];

    if (endian == ENDIAN_LITTLE){
        width  = (head[3] << 8) + head[2];
        height = (head[5] << 8) + head[4];
        form   = (head[7] << 8) + head[6];
    }
    else if (endian == ENDIAN_BIG){
        width  = (head[2] << 8) + head[3];
        height = (head[4] << 8) + head[5];
        form   = (head[6] << 8) + head[7];
    }
    else return false;

    channels        = (uint16_t)(form & 0x0003);
    bitsForChannel  = (uint16_t)(form & 0x001C) >> 2;

    if (height == 0 || width == 0)  return false;
    if ( (form & 0xFF00) != 0 )     return false;

    if      ( channels == 0 ) channels = 1;
    else if ( channels == 2 ) channels = 3;
    else if ( channels == 3 ) channels = 4;

    if      ( bitsForChannel == 0 ) bitsForChannel = 1;
    else if ( bitsForChannel == 3 ) bitsForChannel = 8;
    else if ( bitsForChannel == 4 ) bitsForChannel = 16;
    else return false;

    return true;
}


bool readBlock ( fstream& file_input, uint16_t height,   uint16_t width,
                 uint16_t channels,
                 vector<vector<vector<uint16_t>>>& image, uint16_t bits)
{
    uint16_t x = 0, y = 0;

    while ( x < height ){
        while ( y < width ){
            for (int i = 0; i < channels && file_input.good(); ++i) {
                //cout << "read";
                file_input.read((char*) &image[x][y][i], bits/8);
            }
            if(!file_input.good()) {
                return false;
            }
            y += 1;
        }
        y = 0;
        x += 1;
    }
    return true;
}

void writeHead ( fstream& file_out, uint16_t height,   uint16_t width,
                 uint16_t endian,   uint16_t channels,
                 uint16_t bitsPerChannel )
{
    uint8_t tempBlock[8];
    tempBlock[0] = (uint8_t)(endian >> 8);
    tempBlock[1] = (uint8_t)(endian >> 8);

    if      ( channels == 1 ) channels = 0;
    else if ( channels == 3 ) channels = 2;
    else if ( channels == 4 ) channels = 3;

    if      ( bitsPerChannel == 1 ) bitsPerChannel = 0;
    else if ( bitsPerChannel == 8 ) bitsPerChannel = 3;
    else if ( bitsPerChannel == 16) bitsPerChannel = 4;

    if (endian == ENDIAN_LITTLE){
        tempBlock[2] = (uint8_t)width;
        tempBlock[3] = (uint8_t)(width >> 8);
        tempBlock[4] = (uint8_t)height;
        tempBlock[5] = (uint8_t)(height >> 8);
        tempBlock[6] = (uint8_t)( + (bitsPerChannel << 2) + channels );
        tempBlock[7] = 0;
    }
    else if (endian == ENDIAN_BIG){
        tempBlock[2] = (uint8_t)(width >> 8);
        tempBlock[3] = (uint8_t)width;
        tempBlock[4] = (uint8_t)(height >> 8);
        tempBlock[5] = (uint8_t)height;
        tempBlock[6] = 0;
        tempBlock[7] = (uint8_t )((bitsPerChannel << 2) + channels);
    }

    file_out.write((char*) &tempBlock, 8);
}

bool writeBlockHor ( fstream& file_out, uint16_t height,   uint16_t width,
                     uint16_t channels,
                     vector<vector<vector<uint16_t >>>& image, uint16_t bits)
{
    //cout << "flag" <<endl;
    uint16_t x = 0 , y = width - (uint16_t )1;

    //cout << height << "h" << width << "w" " "<< endl;
    //cout << x << " " << y << endl;
    while ( x < height ){
        while ( y >= 0 ){
            for (int i = 0; i < channels&& file_out.good(); ++i) {
                //cout << x << "!" << y << "!" << i << "!" << image[x][y][i] <<endl;
                file_out.write((char *) &image[x][y][i], bits/8);
                //cout << "qq";
            }

            if(!file_out.good()) {
                return false;
            }
            if(y==0)
                break;
            y -= 1;
        }
        y = width - (uint16_t )1;
        x += 1;
    }
    return true;
    // cout << "asdfasdfasdfasdfasdfasdfasdf";
}




bool writeBlockAsGod ( fstream& file_out, uint16_t height,   uint16_t width,
                       uint16_t channels,
                       vector<vector<vector<uint16_t >>>& image , uint16_t bits)
{
    uint16_t x = height - (uint16_t )1 , y = width - (uint16_t )1;


    //cout << "As God" << endl;
    //cout << height << "h" << width << "w" " "<< endl;
    //cout << x << " " << y << endl;
    while ( x >=0 ){
        while ( y >= 0 ){
            for (int i = 0; i < channels&& file_out.good(); ++i) {
                //cout << x << "!" << y << "!" << i << image[x][y][i] <<endl;
                file_out.write((char *) &image[x][y][i], bits/8);
                //cout << "qq";
            }
            if(!file_out.good()) {
                return false;
            }
            if(y==0)
                break;
            y -= 1;
        }
        if(x==0)
            break;
        y = width - (uint16_t )1;
        x -= 1;
    }
    // cout << "asdfasdfasdfasdfasdfasdfasdf";
    return true;
}



bool writeBlockVer ( fstream& file_out, uint16_t height,   uint16_t width,
                     uint16_t channels,
                     vector<vector<vector<uint16_t >>>& image , uint16_t bits)
{
    uint16_t x = height - (uint16_t )1 , y = 0;

    //cout << height << "h" << width << "w" " "<< "f" << factor << endl;
    //cout << x << " " << y << endl;
    while ( x >= 0 ){
        while ( y < width ){
            for (int i = 0; i < channels && file_out.good(); ++i) {
                //cout << x << "!" << y << "!" << i << "!" << image[x][y][i] <<endl;

                file_out.write((char *) &image[x][y][i], bits/8);
            }

            if(!file_out.good()) {
                return false;
            }
            y += 1;
        }
        if(x==0)
            break;
        y = 0;
        x -= 1;
    }
    return true;
    //cout << "asdfasdfasdfasdfasdfasdfasdf";
}


bool copyPaste ( fstream& file_out, uint16_t height,   uint16_t width,
                 uint16_t channels,
                 vector<vector<vector<uint16_t >>>& image,uint16_t bits)
{
    uint16_t x = 0, y = 0;



    while ( x < height ){
        while ( y < width ){
            for (int i = 0; i < channels&& file_out.good(); ++i) {
                //cout << x << "!" << y << "!" << i << "!" << image[x][y][i] <<endl;
                file_out.write((char*) &image[x][y][i], bits/8);
            }
            if(!file_out.good()) {
                return false;
            }
            y += 1;
        }
        y = 0;
        x += 1;
    }
    return true;
}



/*



*/
bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical ) {

    uint8_t endBlock[8];
    uint16_t head[8], height = 0, width = 0, endian, form = 0, channels, bitsPerChannel;

    fstream file_input(srcFileName, ios::in | ios::binary);

    if (!file_input.good()){
        file_input.close();
        return false;
    }


    file_input.seekg(0, ios::end);
    int sizeOfImage = (int) file_input.tellg() - 8;
    file_input.seekg(0, ios::beg);

    if (file_input.read((char *) &endBlock, 8).gcount() != sizeof(endBlock)) {
        file_input.close();
        return false;
    }

    for (int i = 0; i < 8; ++i) {
        head[i] = (uint16_t) endBlock[i];
    }


    endian = (head[0] << 8) + head[1];

    if (endBlock[0] == 0x49 && endBlock[1] == 0x49) {
        width = (head[3] << 8) + head[2];
        height = (head[5] << 8) + head[4];
        form = (head[7] << 8) + head[6];
    } else if (endBlock[0] == 0x4d && endBlock[1] == 0x4d) {
        width = (head[2] << 8) + head[3];
        height = (head[4] << 8) + head[5];
        form = (head[6] << 8) + head[7];
    } else {

        file_input.close();
        return false;
    }
    channels = (uint16_t) (form & 0x0003);
    bitsPerChannel = (uint16_t) (form & 0x001C) >> 2;

    if (height == 0 || width == 0) {
        file_input.close();
        return false;
    }
    if ((form & 0xFF00) != 0) {
        file_input.close();
        return false;
    }
    if (channels == 0) channels = 1;
    else if (channels == 2) channels = 3;
    else if (channels == 3) channels = 4;
    else if (channels == 1){
        file_input.close();
        return false;
    }

    if (bitsPerChannel == 0) bitsPerChannel = 1;
    else if (bitsPerChannel == 3) bitsPerChannel = 8;
    else if (bitsPerChannel == 4) bitsPerChannel = 16;
    else {
        file_input.close();
        return false;
    }



    //cout << sizeOfImage << " ?= " << width << " " << height << endl;


    //printf("wid %d hi %d form %d\n", width, height, form);

    //printf("bitsPrCh %d chan %d factor %d\n", bitsPerChannel, channels, factor);

            if (sizeOfImage != width * height * channels *( bitsPerChannel / 8))
            {
                file_input.close();
                return false;
            }



    vector<vector<vector<uint16_t >>> image(height, vector<vector<uint16_t >>(width, vector<uint16_t>(channels)));

    if(!readBlock(file_input, height, width, channels, image,bitsPerChannel))
    {

            file_input.close();
            for(int q = 0 ; q < height ; q++) {
                for (int i = 0; i < width; i++) {
                    image[q][i].clear();
                }
                image[q].clear();
            }
            image.clear();
            return false;
    }


    file_input.close();

    fstream fout(dstFileName, ios::out | ios::binary);


    writeHead(fout, height, width, endian, channels, bitsPerChannel);

    if (!fout.good()) {

        fout.close();
        for(int q = 0 ; q < height ; q++) {
            for (int i = 0; i < width; i++) {
                image[q][i].clear();
            }
            image[q].clear();
        }
        image.clear();
        return false;
    }

    //cout << endl << "what is going on" << endl;


    if (flipVertical && flipHorizontal) {
        //cout << "as god";
        if(!writeBlockAsGod(fout, height, width, channels, image, bitsPerChannel))
        {

                fout.close();
                for(int q = 0 ; q < height ; q++) {
                    for (int i = 0; i < width; i++) {
                        image[q][i].clear();
                    }
                    image[q].clear();
                }
                image.clear();
                return false;
        }
    }


    //cout << endl << "what is going on" << endl;
    if (flipHorizontal&&!flipVertical){
        //cout << "hor";
        if(!writeBlockHor(fout, height, width, channels, image,bitsPerChannel))
        {       fout.close();
            for(int q = 0 ; q < height ; q++) {
                for (int i = 0; i < width; i++) {
                    image[q][i].clear();
                }
                image[q].clear();
            }
            image.clear();
            return false;}
    }


    //cout << endl << "what is going on" << endl;
    if (flipVertical&&!flipHorizontal) {
        //cout<<"ver" << endl;
        if(!writeBlockVer(fout, height, width, channels, image,bitsPerChannel))
        {
            fout.close();
            for(int q = 0 ; q < height ; q++) {
                for (int i = 0; i < width; i++) {
                    image[q][i].clear();
                }
                image[q].clear();
            }
            image.clear();
            return false;
        }
    }

    //cout << endl << "what is going on" << endl;
    if (!flipHorizontal&&!flipVertical){
        //cout << "cpypst";
        if(!copyPaste(fout, height, width, channels, image,bitsPerChannel))
        {
            fout.close();
            for(int q = 0 ; q < height ; q++) {
                for (int i = 0; i < width; i++) {
                    image[q][i].clear();
                }
                image[q].clear();
            }
            image.clear();
            return false;
        }
    }
    //cout << srcFileName << "  " << dstFileName << endl;


    fout.close();
    for(int q = 0 ; q < height ; q++) {
        for (int i = 0; i < width; i++) {
            image[q][i].clear();
        }
        image[q].clear();
    }
    image.clear();

    return fout.good();


}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    ifstream fin1(fileName1, ios::binary);
    ifstream fin2(fileName2, ios::binary);
    if (fin2 && fin2) {
        char ch1, ch2;
        bool result = true;
        while (fin1.get(ch1) && fin2.get(ch2)) {
            fin1.read((char*)&ch1, 1);
            fin2.read((char*)&ch2, 1);
            if (ch1 != ch2) {
                result = false;
                //printf("№ %d  %x!=%x\n",cnt,ch1,ch2);
                break;

            }
        }
        if (result) {
            //cout << "Equal" << endl;
            fin1.close();
            fin2.close();
            return true;
        } else {
            //cout << "Unequal" << endl;
            fin2.close();
            fin1.close();
            return false;
        }
    }

    //cout << "Error opening file!" << endl;
    return false;

}

int main ( void )
{

    assert ( flipImage ( "input_00.img", "output_00.img", true, false )
             && identicalFiles ( "output_00.img", "ref_00.img" ) );
    assert ( flipImage ( "input_04.img", "output_04.img", true, false )
             && identicalFiles ( "output_04.img", "ref_04.img" ) );
    assert ( flipImage ( "input_07.img", "output_07.img", true, false )
             && identicalFiles ( "output_07.img", "ref_07.img" ) );
    assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );
    assert ( flipImage ( "input_03.img", "output_03.img", false, false )
             && identicalFiles ( "output_03.img", "ref_03.img" ) );

    //cout << "wtf"<<endl;
    assert ( flipImage ( "input_01.img", "output_01.img", false, true )
             && identicalFiles ( "output_01.img", "ref_01.img" ) );

    //cout << "wtf"<<endl;
    assert ( flipImage ( "input_06.img", "output_06.img", false, true )
             && identicalFiles ( "output_06.img", "ref_06.img" ) );



    assert ( flipImage ( "input_08.img", "output_08.img", true, true )
             && identicalFiles ( "output_08.img", "ref_08.img" ) );
    assert ( flipImage ( "input_02.img", "output_02.img", true, true )
             && identicalFiles ( "output_02.img", "ref_02.img" ) );
    assert ( flipImage ( "input_05.img", "output_05.img", true, true )
             && identicalFiles ( "output_05.img", "ref_05.img" ) );


    // extra inputs (optional & bonus tests)


    assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
             && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
    assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
             && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
    assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
             && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
    assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
             && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
    assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
             && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
    assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
             && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
    assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
             && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
    assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
             && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
    assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
             && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
    assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
             && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
    assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
             && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
    assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );

    return 0;
}
#endif /* __PROGTEST__ */