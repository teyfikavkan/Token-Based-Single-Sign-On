
/**
  *
  * @file Avkan-Kafkas-Arslanparçasi.h
  * @version 1.0
  * @date 19.05.2017
  * @author Mustafa Teyfik Avkan,Benokan Kafkas,Rojda Arslanparçasý
  * @title Token Based Single Sign On
  *
  */


#include <iostream>
#include <vector>
#include <string>
using namespace std;

// DevelopmentKits is an abstract class to be Usb-Stick object or Smart Card object to connect a port.
class DevelopmentKits
{
public:
	virtual string getKitName() = 0;
};
// UsbKit Class  is a concreate class of  DevelopmentKits. It instantiates a UsbKit object which is refered Usb-Stick.
class UsbKit : public DevelopmentKits
{
public:
	UsbKit() : _kitname("usb-stick") {}
	string getKitName() { return _kitname; }
private:
	string _kitname;

};
//ScKit Class  is a concreate class of  DevelopmentKits. It instantiates a ScKit object which is refered Smart-Card.
class ScKit : public DevelopmentKits
{
public:
	ScKit() : _kitname("smard-card") {}
	string getKitName() { return _kitname; }
private:
	string _kitname;

};

//Port class is based on ports in the computer  to connect smart-card object or usb-stick.
class Port {
public:
	Port(string portName, int usbvalid = 0, int scvalid = 0) : _portName(portName), USBvalid(usbvalid), SCvalid(scvalid) { cout<<portName<<" is ready to use "<<endl;};
	void setPort(DevelopmentKits * kit) { _kit = kit; };
	//It return the a kit in the port if It has a any connection with a kit.
	DevelopmentKits * getPort() { return _kit; }
	string getPortName() { return _portName; };
	//When we put a usb-stick. Usbvalid will set USBvalid=1. It shows us that this connected with a port.
	void setUSBvalid(int usbvalid) { USBvalid = usbvalid; }
	//When we put a smart card reader. setSCvalid will set SCvalid=1. It shows us that this connected with a port.
	void setSCvalid(int scvalid) { SCvalid = scvalid; }
    //It returns us that Usb-sticker has connection with a port or not.
	int getUSBvalid() { return USBvalid; }
	//It returns us that smart card reader has connection with a port or not.
	int getSCvalid() { return SCvalid; }
	~Port(){}
private:
	DevelopmentKits *_kit;
	string _portName;
	int USBvalid;
	int SCvalid;
};
// AbstractIterator is a abstract class to iterate UsbKit or ScKit on the ports to read or write them.
class AbstractIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Port* CurrentItem() const = 0;
	~AbstractIterator(){}
protected:
	AbstractIterator() {};
};

class Collection;
// CollectionIterator is a concrete class of AbstractIterator to iterate UsbKit or ScKit on the ports to read or write them.
class CollectionIterator : public AbstractIterator {
public:
	CollectionIterator(const Collection *collection);
	void First();
	void Next();
	Port* CurrentItem() const;
	bool IsDone()const;
private:
	const Collection *_collection;
	int _current;
};
//AbstractAggregate Class is an abstract class to collect the ports.
class AbstractAggregate {
public:
	virtual ~AbstractAggregate() {};
	virtual AbstractIterator* CreateIterator() = 0;
	virtual void add(Port *) = 0; 		// Not needed for iteration.
	virtual int getCount() const = 0; // Needed for iteration.
	virtual Port * get(int) const = 0; // Needed for iteration.
protected:
	AbstractAggregate() {};
};
//Collection Class is an concreate class of AbstractAggregate Class to collect the ports.
class Collection : public AbstractAggregate {
private:
	vector<Port*> _ports;
public:
	CollectionIterator* CreateIterator() {
		return new CollectionIterator(this);
	}
	int getCount() const { return _ports.size(); }
	void add(Port *port) { _ports.push_back(port); };
	Port * get(int index) const { return _ports[index]; };
};
