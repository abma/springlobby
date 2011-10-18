#include "IDownloader.h"

#include "Http/HttpDownloader.h"
#include "Rapid/RapidDownloader.h"
#include "Plasma/PlasmaDownloader.h"
#include "Widget/WidgetDownloader.h"
#include "Util.h"

class IDownloader;

IDownloader* IDownloader::httpdl=NULL;
IDownloader* IDownloader::plasmadl=NULL;
IDownloader* IDownloader::rapiddl=NULL;
IDownloader* IDownloader::widgetdl=NULL;

bool IDownload::addMirror(const std::string& url)
{
	LOG_DEBUG("%s",url.c_str());
	this->mirror.push_back(url);
	return true;
}

bool IDownload::addDepend(const std::string& depend)
{
	this->depend.push_back(depend);
	return true;
}

void IDownloader::Initialize()
{
}

void IDownloader::Shutdown()
{
	delete(httpdl);
	delete(plasmadl);
	delete(rapiddl);
}

IDownloader* IDownloader::GetHttpInstance()
{
	if (httpdl==NULL)
		httpdl=new CHttpDownloader();
	return httpdl;
}
IDownloader* IDownloader::GetRapidInstance()
{
	if (rapiddl==NULL)
		rapiddl=new CRapidDownloader();
	return rapiddl;
}
IDownloader* IDownloader::GetPlasmaInstance()
{
	if (plasmadl==NULL)
		plasmadl=new CPlasmaDownloader();
	return plasmadl;
}
IDownloader* IDownloader::GetWidgetInstance()
{
	if (widgetdl==NULL)
		widgetdl=new CWidgetDownloader();
	return widgetdl;
}

bool IDownloader::download(std::list<IDownload*>& download)
 {
	std::list<IDownload*>::iterator it;
	if (download.size()<=0){
		LOG_ERROR("download list empty");
		return false;
	}
	bool res=true;
	for (it=download.begin(); it!=download.end(); ++it) {
		if (!(*it)->downloaded) //don't download twice
			(*it)->downloaded=this->download(*it);
		if (!(*it)->downloaded) {
			res=false;
		}
	}
	return res;
}

