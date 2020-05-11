/** OSMDownloader.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: roseba
 */

#include "OSMDownloader.h"

//std::shared_ptr<CapstoneMappingQueue<char*>> OSMDownloader::mapping_queue = std::make_shared<CapstoneMappingQueue< char*>>();

OSMDownloader::OSMDownloader()
{

    std::cout <<  "OSMD Constructor "<<this<<std::endl;

}

OSMDownloader::~OSMDownloader()
{

    std::cout <<  "OSMD Destructor "<<this  <<std::endl;
}


OSMDownloader::OSMDownloader(const OSMDownloader &other)
{

    std::cout <<  "OSMD copy constructor "<<this <<std::endl;
    mapping_queue = other.mapping_queue;
}

OSMDownloader& OSMDownloader::operator =(const OSMDownloader &other)
{
    std::cout <<  "OSMD copy assignment "<<this  <<std::endl;
    mapping_queue = other.mapping_queue;
    return *this;
}
int OSMDownloader::osm_map_writer(char *data,  size_t size,  size_t nmemb,  void  *writerData){
    if(writerData == NULL)
      return 0;

    CapstoneMappingQueue<char*> *queue =(CapstoneMappingQueue<char*>*)writerData;
//    queue->push(data, size*nmemb);
    return size * nmemb;
}

std::string OSMDownloader::downloadOSMap(bounding_box_t box)
{
    std::stringstream url_stringstream;
    url_stringstream<<OSM_URL<<box.left<<","<<box.bottom<<","<<box.right<<","<<box.top;
    std::cout << url_stringstream.str() <<std::endl;

    CURL *conn = NULL;
    CURLcode code;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::cout << "init_map_curl: "<<init_mapping_curl(conn, url_stringstream.str().c_str())   <<std::endl;
    code = curl_easy_perform(conn);
    if(code != CURLE_OK){
        std::cerr <<  "getting OSM map failed"  <<std::endl;
        return "ERROR";
    }
    curl_easy_cleanup(conn);
    return url_stringstream.str();


}

bool OSMDownloader::init_mapping_curl(CURL *&conn, const char *url)
{
    CURLcode code;
    conn = curl_easy_init();
    if(conn == NULL) {
        std::cerr <<  "Failed to initialize connection.  "  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
    if(code != CURLE_OK){
        std::cerr <<  "setting ERRORBUFFER option failed"  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_URL, url);
    if(code != CURLE_OK){
        std::cerr <<  "setting URL option failed"  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
    if(code != CURLE_OK){
        std::cerr <<  "setting redirect option failed"  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, osm_map_writer);
    if(code != CURLE_OK){
        std::cerr <<  "setting writer callback option failed"  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, (void *)&buffer );
    if(code != CURLE_OK){
        std::cerr <<  "setting write data option failed"  <<std::endl;
        return false;
    }
    return true;
}


