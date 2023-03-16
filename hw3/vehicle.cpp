//Your declarations and implementations would go here
class Vehicle

{
public:
    Vehicle(string vehicle);
    virtual ~Vehicle();
    virtual string id() const;
    virtual bool canHover() const;
    virtual string description() const = 0;

private:
    string m_id;
};

Vehicle::Vehicle(string vehicle) : m_id(vehicle)
{
}

Vehicle::~Vehicle()
{
}

string Vehicle::id() const
{
    return "" + m_id;
}

bool Vehicle::canHover() const
{
    return true;
}


class Drone : public Vehicle 
{
public:
    Drone(string drone);
    virtual ~Drone();
    virtual bool canHover() const;
    virtual string description() const;
};

Drone::Drone(string drone) :Vehicle(drone)
{
}

Drone::~Drone()
{
    cout << "Destroying " + id() + ", a drone" << endl;
}

string Drone::description() const
{
    return "a drone";
}

bool Drone::canHover() const
{
    return true;
}


class Balloon : public Vehicle 
{
public:
    Balloon(string balloon, double diam);
    virtual ~Balloon();
    virtual bool canHover() const;
    virtual string description() const;
private:
    double m_diameter;
};

Balloon::Balloon(string balloon, double diam) :Vehicle(balloon)
{
    m_diameter = diam;
}

Balloon::~Balloon()
{
    cout << "Destroying the balloon " + id() << endl;
}

string Balloon::description() const
{
    if (m_diameter >= 8)
        return "a large balloon";

    return "a small balloon";
}

bool Balloon::canHover() const
{
    return true;
}


class Satellite : public Vehicle 
{
public:
    Satellite(string drone);
    virtual ~Satellite();
    virtual bool canHover() const;
    virtual string description() const;
};

Satellite::Satellite(string satellite) :Vehicle(satellite)
{
}

Satellite::~Satellite()
{
    cout << "Destroying the satellite " + id() << endl;
}

string Satellite::description() const
{
    return "a satellite";
}

bool Satellite::canHover() const
{
    return false;
}
