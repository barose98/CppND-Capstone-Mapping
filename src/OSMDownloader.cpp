/** OSMDownloader.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: Barrett Rose
 */

#include "OSMDownloader.h"

//std::shared_ptr<CapstoneMappingQueue<char*>> OSMDownloader::mapping_queue = std::make_shared<CapstoneMappingQueue< char*>>();

OSMDownloader::OSMDownloader(std::shared_ptr<OSMDownloadQueue<std::string>> queue)
: downloader_queue(queue)
{
//    std::cout <<  "OSM Downloader Constructor "<<this<<std::endl;
}
OSMDownloader::OSMDownloader(const OSMDownloader &other)
{
//    std::cout <<  "OSM Downloader Copy Constructor "<<this<<std::endl;
    this->downloader_queue = other.downloader_queue;
}

OSMDownloader::OSMDownloader(OSMDownloader &&other)
{
//    std::cout <<  "OSM Downloader Move Constructor "<<this<<std::endl;
        this->downloader_queue = other.downloader_queue;
}

OSMDownloader OSMDownloader::operator =(const OSMDownloader &other)
{
//    std::cout <<  "OSM Downloader Copy Assignment Constructor "<<this<<std::endl;
        this->downloader_queue = other.downloader_queue;
        return *this;
}

OSMDownloader OSMDownloader::operator =(OSMDownloader &&other)
{
//    std::cout <<  "OSM Downloader Move Assignment  Constructor "<<this<<std::endl;
        this->downloader_queue = other.downloader_queue;
        return *this;
}
OSMDownloader::~OSMDownloader()
{

//    std::cout <<  "OSM Downloader Destructor "<<this  <<std::endl;
}

int OSMDownloader::osmHeaderWriter(char *data,  size_t size,  size_t nmemb,  std::shared_ptr<OSMDownloadQueue< std::string>>  *writerData)
{
     return size * nmemb;
}

int OSMDownloader::osmMapWriter(char *data,  size_t size,  size_t nmemb,  std::shared_ptr<OSMDownloadQueue< std::string>>  *writerData){
    if(writerData == NULL)
      return 0;
    std::shared_ptr<OSMDownloadQueue< std::string>> queue =(std::shared_ptr<OSMDownloadQueue< std::string>>) *writerData;
    std::string chunk = std::string(data);
    if(chunk.find(">Error<") !=  std::string::npos ){
        queue->push("<downloaderError/>");
        return size * nmemb;
    }
    queue->push(chunk);
    return size * nmemb;
}

std::string OSMDownloader::downloadOSMap(bounding_box_t box)
{
    std::stringstream url_stringstream;
    url_stringstream<<OSM_URL<<"?data=[maxsize:13421772];way("<<box.south<<","<<box.west<<","<<box.north<<","<<box.east<<");(._;>;);out;";

    downloadStarted  = std::chrono::system_clock::now();
    std::cout <<  "Download started "  <<std::endl;
    CURL *conn = NULL;
    CURLcode code;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    if(!initMappingCurl(conn, url_stringstream.str().c_str()) )
    {
    std::cout << "init_map_curl failed:  "<< errorBuffer  <<std::endl;
    downloader_queue->push("<downloaderError/>");
    }

    code = curl_easy_perform(conn);
    if(code != CURLE_OK){
        std::cerr <<  "Getting OSM map failed: "<< errorBuffer   <<std::endl;
        downloader_queue->push("<downloaderError/>");
        return "ERROR";
    }
    long timeSinceDownloadStarted= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - downloadStarted).count();
    std::cout << "Download took "<<timeSinceDownloadStarted<<" milliseconds"  <<std::endl;

    curl_easy_cleanup(conn);
    return url_stringstream.str();


}

bool OSMDownloader::initMappingCurl(CURL *&conn, const char *url)
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
    code = curl_easy_setopt(conn, CURLOPT_HEADERFUNCTION, osmHeaderWriter);
    if(code != CURLE_OK){
        std::cerr <<  "setting header callback option failed"  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, osmMapWriter);
    if(code != CURLE_OK){
        std::cerr <<  "setting writer callback option failed"  <<std::endl;
        return false;
    }
    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &downloader_queue);
    if(code != CURLE_OK){
        std::cerr <<  "setting write data option failed"  <<std::endl;
        return false;
    }
    return true;
}


