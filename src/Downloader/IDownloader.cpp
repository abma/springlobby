
#include "IDownloader.h"

#include "Http/HttpDownloader.h"
#include "Rapid/RapidDownloader.h"
#include "Plasma/PlasmaDownloader.h"
#include "Torrent/TorrentDownloader.h"

class IDownloader;

IDownloader* IDownloader::httpdl=NULL;
IDownloader* IDownloader::plasmadl=NULL;
IDownloader* IDownloader::rapiddl=NULL;
IDownloader* IDownloader::torrentdl=NULL;

IDownload::IDownload(const std::string& url, const std::string& name){
	this->url=url;
	this->name=name;
}


bool IDownload::addMirror(const std::string& url){
	this->mirror.push_back(url);
	return true;
}

const IDownload* IDownloader::addDownload(const std::string& url, const std::string& filename){
	IDownload* dl=new IDownload(url,filename);
	downloads.push_back(dl);
	return dl;
}

bool IDownloader::removeDownload(IDownload& download){
	this->downloads.remove(&download);
	return true;
}

void IDownloader::Initialize(){
 	httpdl=new CHttpDownloader();
	plasmadl=new CPlasmaDownloader();
	rapiddl=new CRapidDownloader();
	torrentdl=new CTorrentDownloader();
}

void IDownloader::Shutdown(){
	delete(httpdl);
	delete(plasmadl);
	delete(rapiddl);
	delete(torrentdl);
}


