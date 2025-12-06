// main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// UI manager to keep resolution-independent sizing and z-order
struct UIManager
{
    float baseWidth = 1366.0f;
    float baseHeight = 768.0f;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    void beginFrame(const sf::Vector2u &winSize)
    {
        scaleX = winSize.x / baseWidth;
        scaleY = winSize.y / baseHeight;
    }
    float sx(float v) const { return v * scaleX; }
    float sy(float v) const { return v * scaleY; }
    sf::Vector2f s(const sf::Vector2f &v) const { return sf::Vector2f(sx(v.x), sy(v.y)); }
};

template <typename T>
inline T minValue(const T &a, const T &b)
{
    return (a < b) ? a : b;
}

template <typename T>
inline T maxValue(const T &a, const T &b)
{
    return (a > b) ? a : b;
}

template <typename T>
inline T clampValue(const T &value, const T &minVal, const T &maxVal)
{
    return maxValue(minVal, minValue(value, maxVal));
}

template <typename T>
inline void swapValues(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

struct ThemePalette
{
    sf::Color windowClear;
    sf::Color panelGlow;
    sf::Color panelBackground;
    sf::Color panelOutline;
    sf::Color panelAccent;
    sf::Color headerText;
    sf::Color statsText;
    sf::Color dropdownFill;
    sf::Color dropdownOutline;
    sf::Color dropdownText;
    sf::Color dropdownEntry;
    sf::Color dropdownEntrySelected;
    sf::Color dropdownEntryHighlight;
    sf::Color dropdownEntryOutline;
    sf::Color buttonHalo;
    sf::Color buttonFill;
    sf::Color buttonActiveFill;
    sf::Color buttonOutline;
    sf::Color buttonAccent;
    sf::Color buttonText;
    sf::Color detailsFill;
    sf::Color detailsOutline;
    sf::Color detailsAccent;
    sf::Color detailsText;
    sf::Color sidePanelBackground;
    sf::Color sidePanelOutline;
    sf::Color sidePanelHeading;
    sf::Color sidePanelText;
    sf::Color plannedRow;
    sf::Color plannedRowHighlight;
    sf::Color plannedRowOutline;
    sf::Color startButtonFill;
    sf::Color startButtonText;
    sf::Color runningCard;
    sf::Color runningCardOutline;
    sf::Color progressBg;
    sf::Color progressFill;
    sf::Color completedRow;
    sf::Color completedText;
    sf::Color messageText;
};

struct ThemeDefinition
{
    const char *name;
    const char *tagline;
    ThemePalette palette;
};

static ThemePalette makeNeonTheme()
{
    ThemePalette p;
    p.windowClear = sf::Color(6, 12, 26);
    p.panelGlow = sf::Color(0, 220, 255, 35);
    p.panelBackground = sf::Color(10, 16, 32, 235);
    p.panelOutline = sf::Color(0, 255, 210, 80);
    p.panelAccent = sf::Color(0, 200, 255, 140);
    p.headerText = sf::Color(0, 245, 255);
    p.statsText = sf::Color(200, 230, 255);
    p.dropdownFill = sf::Color(16, 30, 58, 230);
    p.dropdownOutline = sf::Color(0, 200, 255, 140);
    p.dropdownText = sf::Color(215, 230, 255);
    p.dropdownEntry = sf::Color(18, 32, 60, 230);
    p.dropdownEntrySelected = sf::Color(30, 90, 150, 230);
    p.dropdownEntryHighlight = sf::Color(0, 170, 255, 200);
    p.dropdownEntryOutline = sf::Color(0, 255, 220, 180);
    p.buttonHalo = sf::Color(0, 220, 255, 75);
    p.buttonFill = sf::Color(18, 40, 78);
    p.buttonActiveFill = sf::Color(22, 120, 180);
    p.buttonOutline = sf::Color(0, 160, 255, 200);
    p.buttonAccent = sf::Color(0, 200, 255, 150);
    p.buttonText = sf::Color(230, 240, 255);
    p.detailsFill = sf::Color(18, 40, 78);
    p.detailsOutline = sf::Color(0, 200, 255);
    p.detailsAccent = sf::Color(0, 220, 255, 180);
    p.detailsText = sf::Color(230, 240, 255);
    p.sidePanelBackground = sf::Color(18, 26, 40, 240);
    p.sidePanelOutline = sf::Color(10, 14, 22, 255);
    p.sidePanelHeading = sf::Color(200, 220, 255);
    p.sidePanelText = sf::Color(210, 215, 230);
    p.plannedRow = sf::Color(28, 38, 58);
    p.plannedRowHighlight = sf::Color(75, 110, 155);
    p.plannedRowOutline = sf::Color(15, 20, 30);
    p.startButtonFill = sf::Color(60, 170, 70);
    p.startButtonText = sf::Color::White;
    p.runningCard = sf::Color(32, 48, 70);
    p.runningCardOutline = sf::Color(12, 20, 28);
    p.progressBg = sf::Color(20, 30, 45);
    p.progressFill = sf::Color(90, 210, 120);
    p.completedRow = sf::Color(26, 36, 52);
    p.completedText = sf::Color(210, 210, 210);
    p.messageText = sf::Color(200, 200, 255);
    return p;
}

static ThemePalette makeSolarTheme()
{
    ThemePalette p;
    p.windowClear = sf::Color(20, 10, 6);
    p.panelGlow = sf::Color(255, 140, 0, 40);
    p.panelBackground = sf::Color(42, 20, 8, 235);
    p.panelOutline = sf::Color(255, 160, 70, 120);
    p.panelAccent = sf::Color(255, 120, 40, 180);
    p.headerText = sf::Color(255, 210, 120);
    p.statsText = sf::Color(255, 230, 200);
    p.dropdownFill = sf::Color(60, 30, 14, 230);
    p.dropdownOutline = sf::Color(255, 160, 80, 150);
    p.dropdownText = sf::Color(255, 230, 200);
    p.dropdownEntry = sf::Color(55, 28, 20, 230);
    p.dropdownEntrySelected = sf::Color(120, 55, 20, 230);
    p.dropdownEntryHighlight = sf::Color(255, 150, 70, 200);
    p.dropdownEntryOutline = sf::Color(255, 200, 140, 170);
    p.buttonHalo = sf::Color(255, 150, 80, 70);
    p.buttonFill = sf::Color(70, 34, 18);
    p.buttonActiveFill = sf::Color(150, 70, 25);
    p.buttonOutline = sf::Color(255, 180, 100, 200);
    p.buttonAccent = sf::Color(255, 150, 70, 160);
    p.buttonText = sf::Color(255, 235, 220);
    p.detailsFill = sf::Color(70, 34, 18);
    p.detailsOutline = sf::Color(255, 150, 70);
    p.detailsAccent = sf::Color(255, 190, 110, 180);
    p.detailsText = sf::Color(255, 235, 220);
    p.sidePanelBackground = sf::Color(50, 18, 10, 240);
    p.sidePanelOutline = sf::Color(80, 30, 16, 255);
    p.sidePanelHeading = sf::Color(255, 210, 150);
    p.sidePanelText = sf::Color(255, 220, 190);
    p.plannedRow = sf::Color(65, 28, 16);
    p.plannedRowHighlight = sf::Color(140, 70, 30);
    p.plannedRowOutline = sf::Color(30, 12, 8);
    p.startButtonFill = sf::Color(255, 120, 60);
    p.startButtonText = sf::Color(25, 10, 4);
    p.runningCard = sf::Color(70, 32, 20);
    p.runningCardOutline = sf::Color(30, 12, 8);
    p.progressBg = sf::Color(40, 18, 10);
    p.progressFill = sf::Color(255, 170, 70);
    p.completedRow = sf::Color(60, 24, 14);
    p.completedText = sf::Color(255, 220, 190);
    p.messageText = sf::Color(255, 210, 160);
    return p;
}

static ThemePalette makeObsidianTheme()
{
    ThemePalette p;
    p.windowClear = sf::Color(2, 2, 8);
    p.panelGlow = sf::Color(180, 0, 255, 30);
    p.panelBackground = sf::Color(12, 8, 26, 240);
    p.panelOutline = sf::Color(160, 90, 255, 120);
    p.panelAccent = sf::Color(150, 70, 255, 160);
    p.headerText = sf::Color(220, 190, 255);
    p.statsText = sf::Color(205, 190, 240);
    p.dropdownFill = sf::Color(24, 16, 48, 230);
    p.dropdownOutline = sf::Color(150, 90, 255, 150);
    p.dropdownText = sf::Color(225, 210, 255);
    p.dropdownEntry = sf::Color(20, 14, 34, 230);
    p.dropdownEntrySelected = sf::Color(70, 40, 110, 230);
    p.dropdownEntryHighlight = sf::Color(190, 120, 255, 200);
    p.dropdownEntryOutline = sf::Color(200, 120, 255, 160);
    p.buttonHalo = sf::Color(190, 120, 255, 60);
    p.buttonFill = sf::Color(26, 18, 52);
    p.buttonActiveFill = sf::Color(90, 50, 150);
    p.buttonOutline = sf::Color(190, 120, 255, 200);
    p.buttonAccent = sf::Color(200, 120, 255, 170);
    p.buttonText = sf::Color(235, 220, 255);
    p.detailsFill = sf::Color(26, 18, 52);
    p.detailsOutline = sf::Color(200, 120, 255);
    p.detailsAccent = sf::Color(220, 150, 255, 190);
    p.detailsText = sf::Color(235, 220, 255);
    p.sidePanelBackground = sf::Color(16, 10, 30, 240);
    p.sidePanelOutline = sf::Color(50, 30, 70, 255);
    p.sidePanelHeading = sf::Color(215, 200, 255);
    p.sidePanelText = sf::Color(200, 190, 230);
    p.plannedRow = sf::Color(34, 22, 58);
    p.plannedRowHighlight = sf::Color(90, 60, 150);
    p.plannedRowOutline = sf::Color(18, 12, 28);
    p.startButtonFill = sf::Color(120, 70, 200);
    p.startButtonText = sf::Color(255, 240, 255);
    p.runningCard = sf::Color(34, 20, 60);
    p.runningCardOutline = sf::Color(16, 8, 30);
    p.progressBg = sf::Color(20, 12, 36);
    p.progressFill = sf::Color(200, 120, 255);
    p.completedRow = sf::Color(28, 16, 48);
    p.completedText = sf::Color(215, 205, 240);
    p.messageText = sf::Color(210, 200, 255);
    return p;
}

static ThemeDefinition gThemeDefinitions[] = {
    {"Neon Tides", "Electroluminescent blues", makeNeonTheme()},
    {"Solar Winds", "Sunset-hued logistics", makeSolarTheme()},
    {"Obsidian Drift", "Deep space purples", makeObsidianTheme()}};

static constexpr int kThemeCount = sizeof(gThemeDefinitions) / sizeof(gThemeDefinitions[0]);
static int gCurrentThemeIndex = 0;
static ThemePalette gThemePalette = gThemeDefinitions[gCurrentThemeIndex].palette;

static void applyTheme(int index)
{
    if (index < 0)
        index = 0;
    if (index >= kThemeCount)
        index = kThemeCount - 1;
    gCurrentThemeIndex = index;
    gThemePalette = gThemeDefinitions[gCurrentThemeIndex].palette;
}

#define MAX_PORTS 512
#define MAX_ROUTES 2048
#define MAX_NAME_LEN 64
#define MAX_COMPANY_LEN 64
#define MAX_TEXT_BUFFER 256

static const float MIN_HANDLING_HOURS = 6.0f;
static const float EXTRA_CHARGE_THRESHOLD = 12.0f;
static const float HOURS_PER_DAY = 24.0f;

enum RouteSearchMode
{
    SearchCheapest = 0,
    SearchFastest = 1
};

enum RouteDisplayFilter
{
    DisplayAllRoutes = 0,
    DisplayDirectOnly,
    DisplayConnectingOnly
};

template <typename T>
class DynamicArray
{
public:
    T *data;
    int capacity;
    int size;
    DynamicArray(int initial = 16)
    {
        capacity = initial;
        size = 0;
        data = new T[capacity];
    }
    DynamicArray(const DynamicArray &other)
    {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    DynamicArray &operator=(const DynamicArray &other)
    {
        if (this == &other)
            return *this;
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
        return *this;
    }
    DynamicArray(DynamicArray &&other) noexcept
    {
        data = other.data;
        capacity = other.capacity;
        size = other.size;
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    DynamicArray &operator=(DynamicArray &&other) noexcept
    {
        if (this == &other)
            return *this;
        delete[] data;
        data = other.data;
        capacity = other.capacity;
        size = other.size;
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
        return *this;
    }
    ~DynamicArray()
    {
        delete[] data;
    }
    void push_back(const T &value)
    {
        if (size >= capacity)
        {
            int newCap = capacity * 2;
            T *newData = new T[newCap];
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCap;
        }
        data[size++] = value;
    }
    T &operator[](int index)
    {
        return data[index];
    }
    const T &operator[](int index) const
    {
        return data[index];
    }
    void resize(int newSize)
    {
        if (newSize < 0)
            return;
        if (newSize > capacity)
        {
            int newCap = capacity;
            while (newCap < newSize)
            {
                newCap *= 2;
            }
            T *newData = new T[newCap];
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCap;
        }
        if (newSize > size)
        {
            for (int i = size; i < newSize; ++i)
            {
                data[i] = T();
            }
        }
        size = newSize;
    }
    void clear() { size = 0; }
};

template <typename T>
struct QueueNode
{
    T value;
    QueueNode<T> *next;
    QueueNode(const T &v) : value(v), next(nullptr) {}
};

template <typename T>
class CustomQueue
{
public:
    QueueNode<T> *head;
    QueueNode<T> *tail;
    int count;
    CustomQueue() : head(nullptr), tail(nullptr), count(0) {}
    ~CustomQueue()
    {
        clear();
    }
    void push(const T &val)
    {
        QueueNode<T> *node = new QueueNode<T>(val);
        if (!tail)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        count++;
    }
    void pop()
    {
        if (!head)
            return;
        QueueNode<T> *tmp = head;
        head = head->next;
        if (!head)
            tail = nullptr;
        delete tmp;
        count--;
    }
    T &front()
    {
        return head->value;
    }
    bool empty() const
    {
        return head == nullptr;
    }
    int size() const
    {
        return count;
    }
    void clear()
    {
        while (head)
        {
            QueueNode<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        count = 0;
    }
};

// ============================================================================
// Custom Stack (linked list based)
// ============================================================================
template <typename T>
class CustomStack
{
public:
    struct Node
    {
        T value;
        Node *next;
        Node(const T &v, Node *n) : value(v), next(n) {}
    };
    Node *topNode;
    int count;
    CustomStack() : topNode(nullptr), count(0) {}
    ~CustomStack()
    {
        while (topNode)
        {
            Node *tmp = topNode;
            topNode = topNode->next;
            delete tmp;
        }
    }
    void push(const T &val)
    {
        topNode = new Node(val, topNode);
        count++;
    }
    void pop()
    {
        if (!topNode)
            return;
        Node *tmp = topNode;
        topNode = topNode->next;
        delete tmp;
        count--;
    }
    T &top()
    {
        return topNode->value;
    }
    bool empty() const
    {
        return topNode == nullptr;
    }
    int size() const
    {
        return count;
    }
};

// ============================================================================
// Custom Min-Heap (binary heap)
// ============================================================================
template <typename T>
class MinHeap
{
public:
    T *data;
    int capacity;
    int heapSize;
    bool (*cmp)(const T &, const T &);
    MinHeap(int cap = 256, bool (*c)(const T &, const T &) = nullptr)
    {
        capacity = cap;
        heapSize = 0;
        data = new T[capacity];
        cmp = c;
    }
    ~MinHeap()
    {
        delete[] data;
    }
    void resize()
    {
        int newCap = capacity * 2;
        T *newData = new T[newCap];
        for (int i = 0; i < heapSize; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }
    void push(const T &val)
    {
        if (heapSize >= capacity)
            resize();
        data[heapSize] = val;
        heapifyUp(heapSize++);
    }
    bool empty() const
    {
        return heapSize == 0;
    }
    T pop()
    {
        if (heapSize == 0)
            return data[0];
        T topVal = data[0];
        data[0] = data[heapSize - 1];
        heapSize--;
        heapifyDown(0);
        return topVal;
    }

private:
    void heapifyUp(int idx)
    {
        while (idx > 0)
        {
            int p = (idx - 1) / 2;
            if (cmp && cmp(data[idx], data[p]))
            {
                T tmp = data[idx];
                data[idx] = data[p];
                data[p] = tmp;
                idx = p;
            }
            else
            {
                break;
            }
        }
    }
    void heapifyDown(int idx)
    {
        while (true)
        {
            int left = idx * 2 + 1;
            int right = left + 1;
            int best = idx;
            if (left < heapSize && cmp && cmp(data[left], data[best]))
                best = left;
            if (right < heapSize && cmp && cmp(data[right], data[best]))
                best = right;
            if (best != idx)
            {
                T tmp = data[idx];
                data[idx] = data[best];
                data[best] = tmp;
                idx = best;
            }
            else
            {
                break;
            }
        }
    }
};

// ============================================================================
// Data structures for graph
// ============================================================================
struct ShipArrival
{
    int shipId;
    float requestedArrivalHours;
    float handlingHours;
    float actualStartHours;
    float actualDepartureHours;
    int slotAssigned;
    char origin[MAX_NAME_LEN];
    char destination[MAX_NAME_LEN];
};

struct RouteEdge
{
    int routeID;
    int originIndex;
    int destIndex;
    char departureDate[16];
    char departureTime[16];
    char arrivalTime[16];
    int costUSD;
    char companyName[MAX_COMPANY_LEN];
    float durationHours;
    float departureHours;
    float arrivalHours;
};

struct CompanyOption
{
    char name[MAX_COMPANY_LEN];
    bool selected;
    CompanyOption() : selected(false)
    {
        name[0] = '\0';
    }
};

struct Port
{
    char name[MAX_NAME_LEN];
    float latitude;
    float longitude;
    int chargePerDay;
    int dockSlots;
    CustomQueue<ShipArrival> dockQueue;
    Port() : latitude(0), longitude(0), chargePerDay(0), dockSlots(2)
    {
        name[0] = '\0';
    }
};

struct AdjacencyNode
{
    RouteEdge *edge;
    AdjacencyNode *next;
};

struct Graph
{
    Port ports[MAX_PORTS];
    int totalPorts;
    RouteEdge routes[MAX_ROUTES];
    int totalRoutes;
    AdjacencyNode *adjacency[MAX_PORTS];
    Graph()
    {
        totalPorts = 0;
        totalRoutes = 0;
        for (int i = 0; i < MAX_PORTS; ++i)
        {
            adjacency[i] = nullptr;
        }
    }
};

enum BoatState
{
    BoatTraveling,
    BoatWaitingInQueue,
    BoatAtDock,
    BoatCompleted
};

struct AnimatedBoat
{
    int routePlanIndex;
    int currentLegIndex;
    BoatState state;
    float progress;
    sf::Vector2f position;
    float currentAngle;
    float simulationTime;
    float waitStartTime;
    float dockingStartTime;
    int currentFrame;
    float frameTime;
    bool active;
    AnimatedBoat() : routePlanIndex(-1), currentLegIndex(0), state(BoatTraveling),
                     progress(0.0f), position(0, 0), currentAngle(0), simulationTime(0),
                     waitStartTime(0), dockingStartTime(0), currentFrame(0),
                     frameTime(0), active(false) {}
};

static Graph globalGraph;
static DynamicArray<CompanyOption> gCompanyOptions(16);
static DynamicArray<std::string> gAvailableDates(16);
static DynamicArray<std::string> gAvailableTimes(16);
static DynamicArray<AnimatedBoat> gActiveBoats(8);
static sf::Clock gSimulationClock;
static const int BOAT_SPRITE_COLS = 4;
static const int BOAT_SPRITE_ROWS = 4;
const int GAP = 20;
static const int BOAT_FRAME_WIDTH = 162;
static const int BOAT_FRAME_HEIGHT = 240;
static const float BOAT_FRAME_DURATION = 0.15f;
static const float BOAT_SPEED_MULTIPLIER = 0.5f;
static const char *boatStateToString(BoatState state)
{
    switch (state)
    {
    case BoatTraveling:
        return "Traveling";
    case BoatWaitingInQueue:
        return "Awaiting Dock";
    case BoatAtDock:
        return "Loading / Unloading";
    case BoatCompleted:
        return "Completed";
    default:
        return "Idle";
    }
}

static AnimatedBoat *findActiveBoatForPlan(int planIndex)
{
    for (int i = 0; i < gActiveBoats.size; ++i)
    {
        if (gActiveBoats[i].routePlanIndex == planIndex)
        {
            return &gActiveBoats[i];
        }
    }
    return nullptr;
}
static int gNextShipId = 1;

// ============================================================================
// Utility functions for string handling and lat/lon mapping
// ============================================================================
static bool stringsEqual(const char *a, const char *b)
{
    return strcmp(a, b) == 0;
}

static void trim(char *str)
{
    int len = (int)strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\r' || str[len - 1] == '\n' || str[len - 1] == '\t'))
    {
        str[len - 1] = '\0';
        len--;
    }
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t')
        start++;
    if (start > 0)
    {
        memmove(str, str + start, strlen(str + start) + 1);
    }
}

static void trimString(std::string &value)
{
    size_t start = value.find_first_not_of(" \t\r\n");
    size_t end = value.find_last_not_of(" \t\r\n");
    if (start == std::string::npos)
    {
        value.clear();
    }
    else
    {
        value = value.substr(start, end - start + 1);
    }
}

static float parseDateTimeHours(const char *dateStr, const char *timeStr)
{
    int year = 0, month = 0, day = 0, hour = 0, minute = 0;
    if (std::sscanf(dateStr, "%d%*[^0-9]%d%*[^0-9]%d", &year, &month, &day) != 3)
    {
        year = 2025;
        month = 1;
        day = 1;
    }
    if (std::sscanf(timeStr, "%d%*[^0-9]%d", &hour, &minute) != 2)
    {
        hour = 0;
        minute = 0;
    }
    int dayKey = (year * 372) + (month * 31) + day;
    float hours = (float)(dayKey * 24 + hour) + (float)minute / 60.0f;
    return hours;
}

static float deriveArrivalHours(const char *dateStr, const char *departureTime, const char *arrivalTime)
{
    float dep = parseDateTimeHours(dateStr, departureTime);
    float arr = parseDateTimeHours(dateStr, arrivalTime);
    if (arr < dep)
    {
        arr += HOURS_PER_DAY;
    }
    return arr;
}

static bool stringOptionExists(const DynamicArray<std::string> &list, const std::string &value)
{
    for (int i = 0; i < list.size; ++i)
    {
        if (list[i] == value)
        {
            return true;
        }
    }
    return false;
}

static void registerDateOption(const std::string &value)
{
    if (value.empty())
        return;
    if (!stringOptionExists(gAvailableDates, value))
    {
        gAvailableDates.push_back(value);
    }
}

static void registerTimeOption(const std::string &value)
{
    if (value.empty())
        return;
    if (!stringOptionExists(gAvailableTimes, value))
    {
        gAvailableTimes.push_back(value);
    }
}

static int findStringIndex(const DynamicArray<std::string> &list, const std::string &value)
{
    for (int i = 0; i < list.size; ++i)
    {
        if (list[i] == value)
            return i;
    }
    return -1;
}

static void ensureAnyOption(DynamicArray<std::string> &list)
{
    const std::string anyLabel = "Any";
    int idx = findStringIndex(list, anyLabel);
    if (idx == -1)
    {
        list.push_back(anyLabel);
        idx = list.size - 1;
    }
    while (idx > 0)
    {
        swapValues(list[idx], list[idx - 1]);
        idx--;
    }
}

static int findCompanyOptionIndex(const char *name)
{
    for (int i = 0; i < gCompanyOptions.size; ++i)
    {
        if (stringsEqual(gCompanyOptions[i].name, name))
        {
            return i;
        }
    }
    return -1;
}

static void registerCompanyOption(const std::string &value)
{
    if (value.empty())
        return;
    int idx = findCompanyOptionIndex(value.c_str());
    if (idx >= 0)
        return;
    CompanyOption option;
    std::strncpy(option.name, value.c_str(), MAX_COMPANY_LEN - 1);
    option.name[MAX_COMPANY_LEN - 1] = '\0';
    option.selected = false;
    gCompanyOptions.push_back(option);
}

static void clearCompanySelections()
{
    for (int i = 0; i < gCompanyOptions.size; ++i)
    {
        gCompanyOptions[i].selected = false;
    }
}

static void exclusiveToggleCompany(int index)
{
    if (index < 0 || index >= gCompanyOptions.size)
        return;
    bool wasSelected = gCompanyOptions[index].selected;
    clearCompanySelections();
    gCompanyOptions[index].selected = !wasSelected;
}

static bool hasCompanyPreference()
{
    for (int i = 0; i < gCompanyOptions.size; ++i)
    {
        if (gCompanyOptions[i].selected)
            return true;
    }
    return false;
}

static bool companyAllowed(const char *name, bool enforcePreference)
{
    if (!enforcePreference)
        return true;
    bool any = hasCompanyPreference();
    if (!any)
        return true;
    for (int i = 0; i < gCompanyOptions.size; ++i)
    {
        if (gCompanyOptions[i].selected && stringsEqual(gCompanyOptions[i].name, name))
        {
            return true;
        }
    }
    return false;
}

static bool matchesFirstLegSchedule(const RouteEdge *edge, const char *desiredDate, const char *desiredTime)
{
    if (!desiredDate || desiredDate[0] == '\0')
        return true;
    if (!desiredTime || desiredTime[0] == '\0')
        return stringsEqual(edge->departureDate, desiredDate);
    return stringsEqual(edge->departureDate, desiredDate) && stringsEqual(edge->departureTime, desiredTime);
}

struct CoordLookup
{
    const char *name;
    float lon;
    float lat;
};

static CoordLookup portCoords[] = {
    {"AbuDhabi", 56.3773f, 22.4539f},
    {"Alexandria", 29.9187f, 31.2001f},
    {"Antwerp", 4.4025f, 51.2194f},
    {"Athens", 23.7275f, 37.9838f},
    {"Busan", 129.0756f, 35.1796f},
    {"CapeTown", 18.4241f, -33.9249f},
    {"Chittagong", 91.7832f, 22.3569f},
    {"Colombo", 79.8612f, 6.9271f},
    {"Copenhagen", 12.5683f, 55.6761f},
    {"Doha", 48.5310f, 25.2854f},
    {"Dubai", 58.0708f, 23.7048f},
    {"Dublin", -6.2603f, 53.3498f},
    {"Durban", 31.0218f, -29.8587f},
    {"Genoa", 8.9463f, 44.4056f},
    {"Hamburg", 9.9937f, 53.5511f},
    {"Helsinki", 24.9384f, 60.1699f},
    {"HongKong", 114.1095f, 22.3964f},
    {"Istanbul", 28.9784f, 41.0082f},
    {"Jakarta", 106.8456f, -6.2088f},
    {"Jeddah", 43.1979f, 21.4858f},
    {"Karachi", 67.0011f, 24.8607f},
    {"Lisbon", -9.1393f, 38.7223f},
    {"London", -0.1276f, 51.5072f},
    {"LosAngeles", -118.2437f, 34.0522f},
    {"Manila", 120.9842f, 14.5995f},
    {"Marseille", 5.3698f, 43.2965f},
    {"Melbourne", 144.9631f, -37.8136f},
    {"Montreal", -73.5673f, 45.5017f},
    {"Mumbai", 72.8777f, 19.0760f},
    {"NewYork", -74.0060f, 40.7128f},
    {"Osaka", 135.5023f, 34.6937f},
    {"Oslo", 10.7522f, 59.9139f},
    {"PortLouis", 57.4896f, -20.1609f},
    {"Rotterdam", 4.4792f, 51.9225f},
    {"Shanghai", 121.4737f, 31.2304f},
    {"Singapore", 103.8198f, 1.3521f},
    {"Stockholm", 18.0686f, 59.3293f},
    {"Sydney", 151.2093f, -33.8688f},
    {"Tokyo", 139.6917f, 35.6895f},
    {"Vancouver", -123.1207f, 49.2827f}};
static const int portCoordsCount = sizeof(portCoords) / sizeof(CoordLookup);

// map lat/lon to x,y on 1280x720 map area
static sf::Vector2f mapLatLonToXY(float lon, float lat, float width, float height)
{
    static const float MAP_LON_MIN = -180.0f;
    static const float MAP_LON_MAX = 180.0f;
    static const float MAP_LAT_MIN = -70.0f;
    static const float MAP_LAT_MAX = 90.0f;
    static const float MAP_X_OFFSET = -0.049f; // tweak horizontally if the map background shifts
    static const float MAP_Y_OFFSET = 0.170f;  // negative lifts ports upward, positive pushes down

    float lonRatio = (lon - MAP_LON_MIN) / (MAP_LON_MAX - MAP_LON_MIN);
    float latRatio = (MAP_LAT_MAX - lat) / (MAP_LAT_MAX - MAP_LAT_MIN);
    float x = (lonRatio + MAP_X_OFFSET) * width;
    float y = (latRatio + MAP_Y_OFFSET) * height;
    if (y < 0)
        y = 0;
    if (y > height)
        y = height;
    if (x < 0)
        x = 0;
    if (x > width)
        x = width;
    return sf::Vector2f(x, y);
}

static bool findPortCoordinates(const char *portName, float &lon, float &lat)
{
    for (int i = 0; i < portCoordsCount; ++i)
    {
        if (stringsEqual(portName, portCoords[i].name))
        {
            lon = portCoords[i].lon;
            lat = portCoords[i].lat;
            return true;
        }
    }
    return false;
}

static void autoPlaceCoordinates(const char *portName, float &lon, float &lat, int index)
{
    int hash = 0;
    for (int i = 0; portName[i]; ++i)
    {
        hash = (hash * 131 + portName[i]) % 360;
    }
    lon = -180.0f + (float)(hash % 360);
    lat = -60.0f + (float)((index * 17) % 120);
}

static void clampViewToMap(sf::Vector2f &offset, float zoom, float mapWidth, float mapHeight)
{
    float scaledWidth = mapWidth * zoom;
    float scaledHeight = mapHeight * zoom;
    float minX = mapWidth - scaledWidth;
    float minY = mapHeight - scaledHeight;
    if (scaledWidth <= mapWidth)
    {
        offset.x = (mapWidth - scaledWidth) * 0.5f;
    }
    else
    {
        if (offset.x > 0.0f)
            offset.x = 0.0f;
        if (offset.x < minX)
            offset.x = minX;
    }
    if (scaledHeight <= mapHeight)
    {
        offset.y = (mapHeight - scaledHeight) * 0.5f;
    }
    else
    {
        if (offset.y > 0.0f)
            offset.y = 0.0f;
        if (offset.y < minY)
            offset.y = minY;
    }
}

static void drawOceanLayer(sf::RenderTarget &target, float mapWidth, float mapHeight, const sf::RenderStates &states)
{
    sf::VertexArray ocean(sf::Quads, 4);
    ocean[0].position = sf::Vector2f(0.0f, 0.0f);
    ocean[1].position = sf::Vector2f(mapWidth, 0.0f);
    ocean[2].position = sf::Vector2f(mapWidth, mapHeight);
    ocean[3].position = sf::Vector2f(0.0f, mapHeight);
    ocean[0].color = sf::Color(5, 18, 35);
    ocean[1].color = sf::Color(10, 35, 70);
    ocean[2].color = sf::Color(0, 58, 100);
    ocean[3].color = sf::Color(0, 28, 70);
    target.draw(ocean, states);

    sf::CircleShape gyre(260.0f);
    gyre.setFillColor(sf::Color(255, 255, 255, 12));
    gyre.setOrigin(260.0f, 260.0f);
    gyre.setPosition(mapWidth * 0.35f, mapHeight * 0.55f);
    target.draw(gyre, states);
    gyre.setRadius(180.0f);
    gyre.setOrigin(180.0f, 180.0f);
    gyre.setPosition(mapWidth * 0.74f, mapHeight * 0.32f);
    gyre.setFillColor(sf::Color(255, 255, 255, 8));
    target.draw(gyre, states);
}

static void drawLatLonGrid(sf::RenderTarget &target, float mapWidth, float mapHeight, const sf::RenderStates &states)
{
    sf::VertexArray grid(sf::Lines);
    for (int lon = -180; lon <= 180; lon += 20)
    {
        float t = (float)(lon + 180) / 360.0f;
        float x = t * mapWidth;
        sf::Color c(255, 255, 255, lon == 0 ? 40 : 18);
        grid.append(sf::Vertex(sf::Vector2f(x, 0.0f), c));
        grid.append(sf::Vertex(sf::Vector2f(x, mapHeight), c));
    }
    for (int lat = -80; lat <= 80; lat += 10)
    {
        sf::Vector2f left = mapLatLonToXY(-180.0f, (float)lat, mapWidth, mapHeight);
        sf::Vector2f right = mapLatLonToXY(180.0f, (float)lat, mapWidth, mapHeight);
        sf::Color c(255, 255, 255, lat == 0 ? 50 : 20);
        grid.append(sf::Vertex(left, c));
        grid.append(sf::Vertex(right, c));
    }
    target.draw(grid, states);
}

static sf::Vector2f geoToXY(float lon, float lat, float mapWidth, float mapHeight)
{
    return mapLatLonToXY(lon, lat, mapWidth, mapHeight);
}

static void drawGeoPolygon(sf::RenderTarget &target, const float (*points)[2], int count, sf::Color fill, sf::Color outline, float mapWidth, float mapHeight, const sf::RenderStates &states)
{
    if (count <= 0)
        return;
    sf::ConvexShape land(count);
    for (int i = 0; i < count; ++i)
    {
        sf::Vector2f xy = geoToXY(points[i][0], points[i][1], mapWidth, mapHeight);
        land.setPoint(i, xy);
    }
    land.setFillColor(fill);
    land.setOutlineColor(outline);
    land.setOutlineThickness(1.8f);
    target.draw(land, states);
}

static void drawLandmasses(sf::RenderTarget &target, float mapWidth, float mapHeight, const sf::RenderStates &states)
{
    static const float northAmerica[][2] = {
        {-165.f, 72.f}, {-150.f, 70.f}, {-130.f, 65.f}, {-110.f, 60.f}, {-100.f, 52.f}, {-90.f, 45.f}, {-80.f, 38.f}, {-76.f, 30.f}, {-88.f, 18.f}, {-105.f, 15.f}, {-125.f, 25.f}, {-145.f, 40.f}};
    static const float southAmerica[][2] = {
        {-80.f, 12.f}, {-70.f, 8.f}, {-60.f, -5.f}, {-54.f, -15.f}, {-50.f, -30.f}, {-55.f, -50.f}, {-70.f, -55.f}, {-78.f, -35.f}};
    static const float greenland[][2] = {
        {-52.f, 84.f}, {-30.f, 78.f}, {-20.f, 72.f}, {-45.f, 70.f}, {-60.f, 75.f}};
    static const float eurasia[][2] = {
        {-15.f, 70.f}, {20.f, 72.f}, {60.f, 70.f}, {90.f, 65.f}, {120.f, 60.f}, {150.f, 55.f}, {170.f, 60.f}, {160.f, 40.f}, {135.f, 30.f}, {110.f, 25.f}, {95.f, 20.f}, {70.f, 15.f}, {40.f, 20.f}, {25.f, 32.f}, {10.f, 40.f}, {-5.f, 45.f}};
    static const float india[][2] = {
        {68.f, 27.f}, {78.f, 33.f}, {84.f, 26.f}, {90.f, 22.f}, {82.f, 8.f}, {75.f, 6.f}};
    static const float japan[][2] = {
        {130.f, 45.f}, {141.f, 44.f}, {146.f, 40.f}, {142.f, 35.f}, {134.f, 32.f}};
    static const float africa[][2] = {
        {-20.f, 35.f}, {10.f, 37.f}, {30.f, 32.f}, {45.f, 20.f}, {50.f, 5.f}, {40.f, -10.f}, {30.f, -25.f}, {15.f, -35.f}, {0.f, -35.f}, {-10.f, -10.f}};
    static const float europeIslands[][2] = {
        {-8.f, 58.f}, {2.f, 59.f}, {4.f, 52.f}, {-3.f, 50.f}};
    static const float australia[][2] = {
        {113.f, -12.f}, {154.f, -11.f}, {154.f, -32.f}, {135.f, -44.f}, {115.f, -35.f}};
    static const float newZealand[][2] = {
        {171.f, -34.f}, {179.f, -41.f}, {168.f, -47.f}, {164.f, -42.f}};

    sf::Color landFill(84, 112, 92, 235);
    sf::Color outline(30, 45, 40, 210);

    drawGeoPolygon(target, northAmerica, sizeof(northAmerica) / sizeof(northAmerica[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, southAmerica, sizeof(southAmerica) / sizeof(southAmerica[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, greenland, sizeof(greenland) / sizeof(greenland[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, europeIslands, sizeof(europeIslands) / sizeof(europeIslands[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, eurasia, sizeof(eurasia) / sizeof(eurasia[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, india, sizeof(india) / sizeof(india[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, japan, sizeof(japan) / sizeof(japan[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, africa, sizeof(africa) / sizeof(africa[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, australia, sizeof(australia) / sizeof(australia[0]), landFill, outline, mapWidth, mapHeight, states);
    drawGeoPolygon(target, newZealand, sizeof(newZealand) / sizeof(newZealand[0]), landFill, outline, mapWidth, mapHeight, states);
}

static void drawProceduralMap(sf::RenderWindow &window, float mapWidth, float mapHeight, float zoomLevel, const sf::Vector2f &viewOffset)
{
    sf::RenderStates mapStates;
    mapStates.transform.translate(viewOffset);
    mapStates.transform.scale(zoomLevel, zoomLevel);
    drawOceanLayer(window, mapWidth, mapHeight, mapStates);
    drawLandmasses(window, mapWidth, mapHeight, mapStates);
    drawLatLonGrid(window, mapWidth, mapHeight, mapStates);
}

static void drawMapTextureLayer(sf::RenderWindow &window, const sf::Texture *texture, float mapWidth, float mapHeight, float zoomLevel, const sf::Vector2f &viewOffset)
{
    sf::RenderStates states;
    states.transform.translate(viewOffset);
    states.transform.scale(zoomLevel, zoomLevel);
    if (texture && texture->getSize().x > 0 && texture->getSize().y > 0)
    {
        sf::Sprite sprite(*texture);
        float scaleX = mapWidth / (float)texture->getSize().x;
        float scaleY = mapHeight / (float)texture->getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(0.0f, 0.0f);
        window.draw(sprite, states);
    }
    else
    {
        drawProceduralMap(window, mapWidth, mapHeight, zoomLevel, viewOffset);
        return;
    }
    drawLatLonGrid(window, mapWidth, mapHeight, states);
}

static void drawCompassOverlay(sf::RenderWindow &window, float mapWidth, const sf::Font &font)
{
    sf::Vector2f basePos(mapWidth - 140.0f, 40.0f);
    sf::CircleShape ring(55.0f);
    ring.setFillColor(sf::Color(10, 10, 10, 160));
    ring.setOutlineColor(sf::Color(220, 220, 220, 200));
    ring.setOutlineThickness(2.0f);
    ring.setPosition(basePos);
    window.draw(ring);

    sf::Vector2f center(basePos.x + 55.0f, basePos.y + 55.0f);
    sf::RectangleShape needle(sf::Vector2f(4.0f, 90.0f));
    needle.setFillColor(sf::Color(230, 75, 60));
    needle.setOrigin(2.0f, 80.0f);
    needle.setPosition(center);
    window.draw(needle);

    sf::RectangleShape needleSouth(sf::Vector2f(4.0f, 90.0f));
    needleSouth.setFillColor(sf::Color(70, 160, 255));
    needleSouth.setOrigin(2.0f, 10.0f);
    needleSouth.setPosition(center);
    window.draw(needleSouth);

    const char *labels[4] = {"N", "E", "S", "W"};
    sf::Vector2f offsets[4] = {
        sf::Vector2f(50.0f, -10.0f),
        sf::Vector2f(100.0f, 42.0f),
        sf::Vector2f(52.0f, 94.0f),
        sf::Vector2f(5.0f, 42.0f)};
    for (int i = 0; i < 4; ++i)
    {
        sf::Text t(labels[i], font, 16);
        t.setFillColor(sf::Color::White);
        t.setStyle(sf::Text::Bold);
        t.setPosition(basePos + offsets[i]);
        window.draw(t);
    }
}

static void drawScaleBar(sf::RenderWindow &window, float mapWidth, float windowHeight, const sf::Font &font, float zoomLevel)
{
    const float circumferenceKm = 40075.0f;
    const float kmOptions[4] = {500.0f, 1000.0f, 2000.0f, 4000.0f};
    float chosenKm = kmOptions[0];
    for (int i = 0; i < 4; ++i)
    {
        float worldPixels = (kmOptions[i] / circumferenceKm) * mapWidth;
        float screenPixels = worldPixels * zoomLevel;
        if (screenPixels >= 80.0f && screenPixels <= 220.0f)
        {
            chosenKm = kmOptions[i];
            break;
        }
        if (i == 3 && screenPixels < 80.0f)
        {
            chosenKm = kmOptions[i];
        }
    }
    float barWorldPixels = (chosenKm / circumferenceKm) * mapWidth;
    float barScreenPixels = barWorldPixels * zoomLevel;
    sf::Vector2f base(30.0f, windowHeight - 70.0f);
    sf::RectangleShape bar(sf::Vector2f(barScreenPixels, 8.0f));
    bar.setFillColor(sf::Color(240, 240, 240));
    bar.setPosition(base);
    window.draw(bar);

    sf::RectangleShape ticks(sf::Vector2f(2.0f, 20.0f));
    ticks.setFillColor(sf::Color::White);
    ticks.setPosition(base.x, base.y - 6.0f);
    window.draw(ticks);
    ticks.setPosition(base.x + barScreenPixels - 2.0f, base.y - 6.0f);
    window.draw(ticks);

    char textBuf[64];
    std::snprintf(textBuf, 64, "%.0f km", chosenKm);
    sf::Text label(textBuf, font, 16);
    label.setFillColor(sf::Color::White);
    label.setPosition(base.x, base.y - 28.0f);
    window.draw(label);
}

static float distancePointToSegment(const sf::Vector2f &p, const sf::Vector2f &a, const sf::Vector2f &b)
{
    sf::Vector2f ab = b - a;
    float abLenSq = ab.x * ab.x + ab.y * ab.y;
    if (abLenSq <= 0.0001f)
        return std::sqrt((p.x - a.x) * (p.x - a.x) + (p.y - a.y) * (p.y - a.y));
    float t = ((p - a).x * ab.x + (p - a).y * ab.y) / abLenSq;
    t = maxValue(0.0f, minValue(1.0f, t));
    sf::Vector2f proj = a + ab * t;
    float dx = p.x - proj.x;
    float dy = p.y - proj.y;
    return std::sqrt(dx * dx + dy * dy);
}

static int addOrGetPort(const char *name)
{
    for (int i = 0; i < globalGraph.totalPorts; ++i)
    {
        if (stringsEqual(globalGraph.ports[i].name, name))
        {
            return i;
        }
    }
    int idx = globalGraph.totalPorts++;
    strncpy(globalGraph.ports[idx].name, name, MAX_NAME_LEN - 1);
    globalGraph.ports[idx].name[MAX_NAME_LEN - 1] = '\0';

    float lon = 0, lat = 0;
    if (!findPortCoordinates(name, lon, lat))
    {
        autoPlaceCoordinates(name, lon, lat, idx);
    }
    globalGraph.ports[idx].longitude = lon;
    globalGraph.ports[idx].latitude = lat;
    globalGraph.ports[idx].chargePerDay = 100;
    globalGraph.ports[idx].dockSlots = 3;
    return idx;
}

static int addOrUpdatePortCharge(const char *name, int charge)
{
    int idx = -1;
    for (int i = 0; i < globalGraph.totalPorts; ++i)
    {
        if (stringsEqual(globalGraph.ports[i].name, name))
        {
            idx = i;
            break;
        }
    }
    if (idx < 0)
    {
        idx = addOrGetPort(name);
    }
    globalGraph.ports[idx].chargePerDay = charge;
    return idx;
}

static void addRouteEdge(const RouteEdge &edge)
{
    if (globalGraph.totalRoutes >= MAX_ROUTES)
        return;
    globalGraph.routes[globalGraph.totalRoutes] = edge;
    RouteEdge *stored = &globalGraph.routes[globalGraph.totalRoutes];
    globalGraph.totalRoutes++;
    int origin = edge.originIndex;
    AdjacencyNode *node = new AdjacencyNode();
    node->edge = stored;
    node->next = globalGraph.adjacency[origin];
    globalGraph.adjacency[origin] = node;
}

// ============================================================================
// Parser functions
// ============================================================================
static bool parsePortCharges(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string name = line.substr(0, commaPos);
            std::string chargeStr = line.substr(commaPos + 1);
            trimString(name);
            trimString(chargeStr);
            int c = std::atoi(chargeStr.c_str());
            addOrUpdatePortCharge(name.c_str(), c);
        }
        else
        {
            std::istringstream iss(line);
            std::string name;
            int charge = 0;
            if (!(iss >> name >> charge))
                continue;
            addOrUpdatePortCharge(name.c_str(), charge);
        }
    }
    return true;
}

static bool parseRoutes(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;
    std::string line;
    int nextRouteId = 1;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::istringstream iss(line);
            std::string routeIDStr, origin, dest, depDate, depTime, arrTime, costStr, company;
            if (!std::getline(iss, routeIDStr, ','))
                continue;
            if (!std::getline(iss, origin, ','))
                continue;
            if (!std::getline(iss, dest, ','))
                continue;
            if (!std::getline(iss, depDate, ','))
                continue;
            if (!std::getline(iss, depTime, ','))
                continue;
            if (!std::getline(iss, arrTime, ','))
                continue;
            if (!std::getline(iss, costStr, ','))
                continue;
            if (!std::getline(iss, company))
                continue;

            trimString(routeIDStr);
            trimString(origin);
            trimString(dest);
            trimString(depDate);
            trimString(depTime);
            trimString(arrTime);
            trimString(costStr);
            trimString(company);

            RouteEdge edge;
            edge.routeID = std::atoi(routeIDStr.c_str());
            edge.originIndex = addOrGetPort(origin.c_str());
            edge.destIndex = addOrGetPort(dest.c_str());
            edge.costUSD = std::atoi(costStr.c_str());
            strncpy(edge.departureDate, depDate.c_str(), 15);
            edge.departureDate[15] = '\0';
            strncpy(edge.departureTime, depTime.c_str(), 15);
            edge.departureTime[15] = '\0';
            strncpy(edge.arrivalTime, arrTime.c_str(), 15);
            edge.arrivalTime[15] = '\0';
            strncpy(edge.companyName, company.c_str(), MAX_COMPANY_LEN - 1);
            edge.companyName[MAX_COMPANY_LEN - 1] = '\0';
            edge.departureHours = parseDateTimeHours(edge.departureDate, edge.departureTime);
            edge.arrivalHours = deriveArrivalHours(edge.departureDate, edge.departureTime, edge.arrivalTime);
            edge.durationHours = edge.arrivalHours - edge.departureHours;
            if (edge.durationHours <= 0.0f)
            {
                edge.durationHours = 0.5f;
            }
            registerCompanyOption(company);
            registerDateOption(depDate);
            registerTimeOption(depTime);
            addRouteEdge(edge);
        }
        else
        {
            std::istringstream iss(line);
            std::string origin, dest, depDate, depTime, arrTime, costStr, company;
            if (!(iss >> origin >> dest >> depDate >> depTime >> arrTime >> costStr >> company))
                continue;
            trimString(origin);
            trimString(dest);
            trimString(depDate);
            trimString(depTime);
            trimString(arrTime);
            trimString(costStr);
            trimString(company);
            RouteEdge edge;
            edge.routeID = nextRouteId++;
            edge.originIndex = addOrGetPort(origin.c_str());
            edge.destIndex = addOrGetPort(dest.c_str());
            edge.costUSD = std::atoi(costStr.c_str());
            strncpy(edge.departureDate, depDate.c_str(), 15);
            edge.departureDate[15] = '\0';
            strncpy(edge.departureTime, depTime.c_str(), 15);
            edge.departureTime[15] = '\0';
            strncpy(edge.arrivalTime, arrTime.c_str(), 15);
            edge.arrivalTime[15] = '\0';
            strncpy(edge.companyName, company.c_str(), MAX_COMPANY_LEN - 1);
            edge.companyName[MAX_COMPANY_LEN - 1] = '\0';
            edge.departureHours = parseDateTimeHours(edge.departureDate, edge.departureTime);
            edge.arrivalHours = deriveArrivalHours(edge.departureDate, edge.departureTime, edge.arrivalTime);
            edge.durationHours = edge.arrivalHours - edge.departureHours;
            if (edge.durationHours <= 0.0f)
            {
                edge.durationHours = 0.5f;
            }
            registerCompanyOption(company);
            registerDateOption(depDate);
            registerTimeOption(depTime);
            addRouteEdge(edge);
        }
    }
    return true;
}

static void ensureDefaultRouteOptions()
{
    ensureAnyOption(gAvailableDates);
    ensureAnyOption(gAvailableTimes);
}

// ============================================================================
// Pathfinding structures
// ============================================================================
struct PathNode
{
    int portIndex;
    float cost;
    float heuristic;
    int parent;
    RouteEdge *parentEdge;
    bool operator<(const PathNode &other) const
    {
        return cost < other.cost;
    }
};

static bool cmpPathNode(const PathNode &a, const PathNode &b)
{
    return (a.cost + a.heuristic) < (b.cost + b.heuristic);
}

static float toRadians(float deg)
{
    return deg * (float)M_PI / 180.0f;
}

static float haversineDistance(int portA, int portB)
{
    float lat1 = globalGraph.ports[portA].latitude;
    float lon1 = globalGraph.ports[portA].longitude;
    float lat2 = globalGraph.ports[portB].latitude;
    float lon2 = globalGraph.ports[portB].longitude;
    float dLat = toRadians(lat2 - lat1);
    float dLon = toRadians(lon2 - lon1);
    float a = std::sin(dLat / 2) * std::sin(dLat / 2) +
              std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
                  std::sin(dLon / 2) * std::sin(dLon / 2);
    float c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    float R = 6371.0f;
    return R * c;
}

// ============================================================================
// Docking queue simulation helpers
// ============================================================================
static void queueToArray(const CustomQueue<ShipArrival> &queue, DynamicArray<ShipArrival> &out)
{
    QueueNode<ShipArrival> *node = queue.head;
    while (node)
    {
        out.push_back(node->value);
        node = node->next;
    }
}

static void arrayToQueue(CustomQueue<ShipArrival> &queue, const DynamicArray<ShipArrival> &src)
{
    queue.clear();
    for (int i = 0; i < src.size; ++i)
    {
        queue.push(src[i]);
    }
}

static void sortShipArrivals(DynamicArray<ShipArrival> &arr)
{
    for (int i = 1; i < arr.size; ++i)
    {
        ShipArrival key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].requestedArrivalHours > key.requestedArrivalHours)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

static void cleanupPortQueue(Port &port, float cutoffHours)
{
    int initialCap = maxValue(4, port.dockQueue.count + 4);
    DynamicArray<ShipArrival> items(initialCap);
    queueToArray(port.dockQueue, items);
    DynamicArray<ShipArrival> filtered(initialCap);
    for (int i = 0; i < items.size; ++i)
    {
        if (items[i].actualDepartureHours >= cutoffHours)
        {
            filtered.push_back(items[i]);
        }
    }
    arrayToQueue(port.dockQueue, filtered);
}

static ShipArrival simulateDockingForPort(int portIndex, ShipArrival incoming, float &extraCostOut, float &waitHoursOut)
{
    Port &port = globalGraph.ports[portIndex];
    int initialCap = maxValue(4, port.dockQueue.count + 4);
    DynamicArray<ShipArrival> schedule(initialCap);
    queueToArray(port.dockQueue, schedule);
    schedule.push_back(incoming);
    sortShipArrivals(schedule);

    float slotAvailability[8];
    for (int i = 0; i < 8; ++i)
        slotAvailability[i] = 0.0f;
    int slotCount = maxValue(1, minValue(8, port.dockSlots));

    ShipArrival *tracked = nullptr;
    for (int i = 0; i < schedule.size; ++i)
    {
        ShipArrival &item = schedule[i];
        float bestStart = 1e12f;
        int bestSlot = 0;
        for (int slot = 0; slot < slotCount; ++slot)
        {
            float candidate = item.requestedArrivalHours;
            if (slotAvailability[slot] > candidate)
            {
                candidate = slotAvailability[slot];
            }
            if (candidate < bestStart)
            {
                bestStart = candidate;
                bestSlot = slot;
            }
        }
        item.actualStartHours = bestStart;
        item.actualDepartureHours = bestStart + item.handlingHours;
        item.slotAssigned = bestSlot;
        slotAvailability[bestSlot] = item.actualDepartureHours;
        if (item.shipId == incoming.shipId)
        {
            tracked = &item;
        }
    }

    arrayToQueue(port.dockQueue, schedule);

    ShipArrival resolved = incoming;
    if (tracked)
    {
        resolved = *tracked;
    }

    float totalStay = resolved.actualDepartureHours - resolved.requestedArrivalHours;
    if (totalStay < 0.0f)
        totalStay = 0.0f;
    if (totalStay > EXTRA_CHARGE_THRESHOLD)
    {
        float overtime = totalStay - EXTRA_CHARGE_THRESHOLD;
        float days = std::ceil(overtime / HOURS_PER_DAY);
        extraCostOut = days * (float)port.chargePerDay;
    }
    else
    {
        extraCostOut = 0.0f;
    }
    waitHoursOut = resolved.actualStartHours - resolved.requestedArrivalHours;
    if (waitHoursOut < 0.0f)
        waitHoursOut = 0.0f;
    return resolved;
}

static float portQueueWaitEstimate(const Port &port)
{
    if (port.dockQueue.empty())
        return 0.0f;
    const QueueNode<ShipArrival> *node = port.dockQueue.head;
    float wait = node->value.actualStartHours - node->value.requestedArrivalHours;
    if (wait < 0.0f)
        wait = 0.0f;
    return wait;
}

// ============================================================================
// Dijkstra and A*
// ============================================================================
struct SearchResult
{
    bool found;
    float totalCost;
    float totalTime;
    DynamicArray<RouteEdge *> routeEdges;
    SearchResult() : found(false), totalCost(0), totalTime(0), routeEdges(32) {}
};

struct LegSimulation
{
    RouteEdge *edge;
    float plannedDepartureHours;
    float plannedArrivalHours;
    float actualDepartureHours;
    float actualArrivalHours;
    float waitHours;
    float extraCost;
    bool missedConnection;
    LegSimulation() : edge(nullptr), plannedDepartureHours(0), plannedArrivalHours(0), actualDepartureHours(0), actualArrivalHours(0), waitHours(0), extraCost(0), missedConnection(false) {}
};

struct RoutePlan
{
    SearchResult baseResult;
    DynamicArray<LegSimulation> simulatedLegs;
    float requestedStartHours;
    char requestedDate[16];
    char requestedTime[16];
    float realisticCost;
    float realisticTime;
    bool visible;
    bool isDirect;
    bool preferenceSatisfied;
    bool preferenceRequested;
    RouteSearchMode mode;
    char summary[128];
    bool hasLaunched;
    bool isRunning;
    bool isCompleted;
    float runningProgress;
    RoutePlan() : simulatedLegs(16)
    {
        requestedStartHours = 0.0f;
        requestedDate[0] = '\0';
        requestedTime[0] = '\0';
        realisticCost = 0.0f;
        realisticTime = 0.0f;
        visible = true;
        isDirect = false;
        preferenceSatisfied = true;
        preferenceRequested = false;
        mode = SearchCheapest;
        summary[0] = '\0';
        hasLaunched = false;
        isRunning = false;
        isCompleted = false;
        runningProgress = 0.0f;
    }
};

struct RenderedEdgeSegment
{
    RouteEdge *edge;
    sf::Vector2f start;
    sf::Vector2f end;
    float actualDeparture;
    float actualArrival;
    bool isDirect;
    const LegSimulation *legRef;
};

static DynamicArray<RoutePlan> gPlannedRoutes(8);
static DynamicArray<RenderedEdgeSegment> gRenderableEdges(128);
static DynamicArray<sf::FloatRect> gRouteItemRects(16);
static DynamicArray<int> gRouteItemPlanOrder(16);
static bool sidePanelOpen = false;
static float sidePanelAnim = 0.0f;
static bool gNavPanelOpen = true;
static float gNavPanelAnim = 1.0f;

enum class AppScreen
{
    Menu,
    ThemeSettings,
    Simulation
};

static AppScreen gAppScreen = AppScreen::Menu;
static sf::Texture gMenuTexture;
static bool gMenuTextureLoaded = false;
static sf::Music gBackgroundMusic;
static bool gMusicAvailable = false;
static bool gMusicEnabled = true;

static sf::FloatRect gMenuStartRect;
static sf::FloatRect gMenuSettingsRect;
static sf::FloatRect gMenuExitRect;
static sf::FloatRect gSettingsBackRect;
static DynamicArray<sf::FloatRect> gThemeCardRects(8);
static sf::FloatRect gMusicToggleRect;

static void setMusicState(bool enabled)
{
    gMusicEnabled = enabled;
    if (!gMusicAvailable)
        return;
    if (gMusicEnabled)
    {
        if (gBackgroundMusic.getStatus() != sf::Music::Playing)
        {
            gBackgroundMusic.setLoop(true);
            gBackgroundMusic.play();
        }
    }
    else
    {
        if (gBackgroundMusic.getStatus() == sf::Music::Playing)
        {
            gBackgroundMusic.pause();
        }
    }
}

static void toggleMusic()
{
    setMusicState(!gMusicEnabled);
}

static void layoutMenu(const UIManager &ui, unsigned int width, unsigned int height)
{
    float menuWidth = minValue(ui.sx(520.0f), (float)width * 0.5f);
    float menuX = (float)width * 0.5f - menuWidth * 0.5f;
    float startY = ui.sy(320.0f);
    float buttonHeight = ui.sy(64.0f);
    float spacing = ui.sy(26.0f);
    gMenuStartRect = sf::FloatRect(menuX, startY, menuWidth, buttonHeight);
    gMenuSettingsRect = sf::FloatRect(menuX, startY + buttonHeight + spacing, menuWidth, buttonHeight);
    gMenuExitRect = sf::FloatRect(menuX, startY + (buttonHeight + spacing) * 2.0f, menuWidth, buttonHeight);
    gMusicToggleRect = sf::FloatRect((float)width - ui.sx(190.0f), ui.sy(30.0f), ui.sx(160.0f), ui.sy(36.0f));
    if (gThemeCardRects.size != kThemeCount)
        gThemeCardRects.resize(kThemeCount);
    float settingsWidth = minValue(ui.sx(900.0f), (float)width * 0.9f);
    float settingsX = ((float)width - settingsWidth) * 0.5f;
    float cardWidth = (settingsWidth - ui.sx(40.0f)) / 3.0f;
    float cardHeight = ui.sy(260.0f);
    float cardY = ui.sy(280.0f);
    for (int i = 0; i < kThemeCount; ++i)
    {
        float cardX = settingsX + i * (cardWidth + ui.sx(20.0f));
        gThemeCardRects[i] = sf::FloatRect(cardX, cardY, cardWidth, cardHeight);
    }
    gSettingsBackRect = sf::FloatRect(ui.sx(30.0f), ui.sy(30.0f), ui.sx(140.0f), ui.sy(42.0f));
}

static sf::Color colorWithAlpha(const sf::Color &base, sf::Uint8 alpha)
{
    return sf::Color(base.r, base.g, base.b, alpha);
}

static void drawMenuButton(sf::RenderTarget &target, const sf::FloatRect &rect, const sf::Font &font, const std::string &label, const std::string &subtitle, bool hovered, float pulseStrength)
{
    sf::RectangleShape halo(sf::Vector2f(rect.width + 16.0f, rect.height + 12.0f));
    halo.setPosition(rect.left - 8.0f, rect.top - 6.0f);
    halo.setFillColor(colorWithAlpha(gThemePalette.panelAccent, (sf::Uint8)(hovered ? 120 : 70)));
    target.draw(halo);

    sf::RectangleShape body(sf::Vector2f(rect.width, rect.height));
    body.setPosition(rect.left, rect.top);
    sf::Color base = hovered ? gThemePalette.buttonActiveFill : gThemePalette.buttonFill;
    body.setFillColor(base);
    body.setOutlineThickness(2.5f);
    body.setOutlineColor(hovered ? gThemePalette.buttonOutline : colorWithAlpha(gThemePalette.buttonOutline, 180));
    target.draw(body);

    sf::RectangleShape accent(sf::Vector2f(rect.width, 4.0f));
    accent.setPosition(rect.left, rect.top);
    accent.setFillColor(colorWithAlpha(gThemePalette.buttonAccent, 200));
    target.draw(accent);

    sf::Text title(label, font, 24);
    title.setFillColor(gThemePalette.buttonText);
    title.setPosition(rect.left + 18.0f, rect.top + 10.0f);
    target.draw(title);

    if (!subtitle.empty())
    {
        sf::Text sub(subtitle, font, 14);
        sub.setFillColor(colorWithAlpha(gThemePalette.buttonText, 200));
        sub.setPosition(rect.left + 18.0f, rect.top + rect.height - 28.0f);
        target.draw(sub);
    }

    sf::CircleShape pulse(10.0f + pulseStrength * 4.0f, 32);
    pulse.setOrigin(10.0f + pulseStrength * 4.0f, 10.0f + pulseStrength * 4.0f);
    pulse.setPosition(rect.left + rect.width - 30.0f, rect.top + rect.height * 0.5f);
    pulse.setFillColor(colorWithAlpha(gThemePalette.buttonAccent, hovered ? 180 : 110));
    target.draw(pulse);
}

static void drawMusicToggleControl(sf::RenderTarget &target, const sf::Font &font, const sf::Vector2f &mousePos)
{
    bool hovered = gMusicToggleRect.contains(mousePos);
    sf::RectangleShape bg(sf::Vector2f(gMusicToggleRect.width, gMusicToggleRect.height));
    bg.setPosition(gMusicToggleRect.left, gMusicToggleRect.top);
    bg.setFillColor(colorWithAlpha(gThemePalette.dropdownFill, hovered ? 220 : 180));
    bg.setOutlineColor(hovered ? gThemePalette.dropdownOutline : colorWithAlpha(gThemePalette.dropdownOutline, 120));
    bg.setOutlineThickness(2.0f);
    target.draw(bg);

    sf::Text label(gMusicEnabled ? "Music: ON" : "Music: OFF", font, 16);
    label.setFillColor(gThemePalette.dropdownText);
    label.setPosition(gMusicToggleRect.left + 10.0f, gMusicToggleRect.top + 6.0f);
    target.draw(label);

    float sliderWidth = 36.0f;
    sf::RectangleShape track(sf::Vector2f(sliderWidth, 10.0f));
    track.setPosition(gMusicToggleRect.left + gMusicToggleRect.width - sliderWidth - 14.0f, gMusicToggleRect.top + gMusicToggleRect.height * 0.5f - 5.0f);
    track.setFillColor(colorWithAlpha(gThemePalette.panelAccent, 160));
    target.draw(track);

    sf::CircleShape knob(10.0f);
    knob.setOrigin(10.0f, 10.0f);
    float knobX = gMusicEnabled ? (track.getPosition().x + sliderWidth) : track.getPosition().x;
    knob.setPosition(knobX, track.getPosition().y + 5.0f);
    knob.setFillColor(hovered ? gThemePalette.buttonActiveFill : gThemePalette.buttonFill);
    knob.setOutlineColor(gThemePalette.buttonOutline);
    knob.setOutlineThickness(2.0f);
    target.draw(knob);
}

static void drawOrbitingGlow(sf::RenderTarget &target, float time, unsigned int width, unsigned int height)
{
    sf::CircleShape orb(220.0f, 64);
    orb.setOrigin(220.0f, 220.0f);
    float radius = minValue((float)width, (float)height) * 0.35f;
    float x = width * 0.5f + std::cos(time * 0.5f) * radius * 0.4f;
    float y = height * 0.5f + std::sin(time * 0.6f) * radius * 0.3f;
    orb.setPosition(x, y);
    orb.setFillColor(colorWithAlpha(gThemePalette.panelAccent, 45));
    target.draw(orb);
}

static void drawMainMenu(sf::RenderWindow &window, const sf::Font &font, const UIManager &ui, unsigned int width, unsigned int height, const sf::Vector2f &mousePos, float timeSeconds)
{
    if (gMenuTextureLoaded)
    {
        sf::Sprite bg(gMenuTexture);
        sf::Vector2u texSize = gMenuTexture.getSize();
        float scaleX = (float)width / (float)texSize.x;
        float scaleY = (float)height / (float)texSize.y;
        float scale = maxValue(scaleX, scaleY);
        bg.setScale(scale, scale);
        bg.setPosition((float)width * 0.5f - texSize.x * 0.5f * scale, (float)height * 0.5f - texSize.y * 0.5f * scale);
        window.draw(bg);
    }
    else
    {
        sf::RectangleShape gradient(sf::Vector2f((float)width, (float)height));
        gradient.setFillColor(sf::Color(8, 12, 32));
        window.draw(gradient);
    }

    sf::RectangleShape overlay(sf::Vector2f((float)width, (float)height));
    overlay.setFillColor(sf::Color(2, 4, 16, 140));
    window.draw(overlay);

    drawOrbitingGlow(window, timeSeconds, width, height);

    sf::Text title("OceanRoute Navigator", font, 52);
    title.setFillColor(sf::Color(255, 255, 240));
    title.setPosition(ui.sx(80.0f), ui.sy(90.0f));
    window.draw(title);

    sf::Text tagline("Grand Maritime Control Suite", font, 22);
    tagline.setFillColor(sf::Color(200, 220, 255));
    tagline.setPosition(ui.sx(84.0f), ui.sy(150.0f));
    window.draw(tagline);

    sf::Text blurb("Chart global itineraries, simulate fleets, and orchestrate routes before launch.", font, 18);
    blurb.setFillColor(sf::Color(190, 205, 235));
    blurb.setPosition(ui.sx(84.0f), ui.sy(186.0f));
    window.draw(blurb);

    bool hoverStart = gMenuStartRect.contains(mousePos);
    bool hoverSettings = gMenuSettingsRect.contains(mousePos);
    bool hoverExit = gMenuExitRect.contains(mousePos);
    drawMenuButton(window, gMenuStartRect, font, "Enter Navigation", "Start planning and tracking routes", hoverStart, std::sin(timeSeconds * 2.0f) * 0.5f + 0.5f);
    drawMenuButton(window, gMenuSettingsRect, font, "Theme Studio", "Customize palettes and ambiance", hoverSettings, std::sin(timeSeconds * 1.6f) * 0.5f + 0.5f);
    drawMenuButton(window, gMenuExitRect, font, "Exit", "Leave the bridge", hoverExit, 0.2f);

    drawMusicToggleControl(window, font, mousePos);

    sf::Text footer("© 2025 OceanRoute Systems", font, 14);
    footer.setFillColor(sf::Color(180, 190, 210));
    footer.setPosition(ui.sx(80.0f), (float)height - ui.sy(60.0f));
    window.draw(footer);
}

static void drawThemeCard(sf::RenderTarget &target, const sf::FloatRect &rect, const ThemeDefinition &def, bool selected, bool hovered, const sf::Font &font, float timeSeconds)
{
    sf::RectangleShape card(sf::Vector2f(rect.width, rect.height));
    card.setPosition(rect.left, rect.top);
    sf::Color base = selected ? colorWithAlpha(def.palette.buttonActiveFill, 230) : colorWithAlpha(def.palette.dropdownFill, hovered ? 230 : 200);
    card.setFillColor(base);
    card.setOutlineThickness(selected ? 3.5f : 2.0f);
    card.setOutlineColor(selected ? def.palette.buttonOutline : colorWithAlpha(def.palette.buttonOutline, hovered ? 200 : 110));
    target.draw(card);

    sf::Text title(def.name, font, 22);
    title.setFillColor(def.palette.buttonText);
    title.setPosition(rect.left + 16.0f, rect.top + 18.0f);
    target.draw(title);

    sf::Text tagline(def.tagline, font, 16);
    tagline.setFillColor(colorWithAlpha(def.palette.buttonText, 215));
    tagline.setPosition(rect.left + 16.0f, rect.top + 50.0f);
    target.draw(tagline);

    float swatchWidth = (rect.width - 32.0f) / 4.0f;
    float swatchY = rect.top + rect.height - 70.0f;
    sf::Color swatches[4] = {def.palette.panelAccent, def.palette.buttonFill, def.palette.runningCard, def.palette.progressFill};
    for (int i = 0; i < 4; ++i)
    {
        sf::RectangleShape swatch(sf::Vector2f(swatchWidth - 10.0f, 34.0f));
        swatch.setPosition(rect.left + 16.0f + i * (swatchWidth + 2.0f), swatchY);
        swatch.setFillColor(swatches[i]);
        target.draw(swatch);
    }

    sf::Text hint(selected ? "Active" : (hovered ? "Click to apply" : ""), font, 14);
    hint.setFillColor(selected ? sf::Color(0, 255, 210) : sf::Color(200, 210, 230));
    hint.setPosition(rect.left + 16.0f, rect.top + rect.height - 30.0f);
    target.draw(hint);
}

static void drawThemeSettings(sf::RenderWindow &window, const sf::Font &font, const UIManager &ui, unsigned int width, unsigned int height, const sf::Vector2f &mousePos, float timeSeconds)
{
    if (gMenuTextureLoaded)
    {
        sf::Sprite bg(gMenuTexture);
        sf::Vector2u texSize = gMenuTexture.getSize();
        float scaleX = (float)width / (float)texSize.x;
        float scaleY = (float)height / (float)texSize.y;
        float scale = maxValue(scaleX, scaleY);
        bg.setScale(scale, scale);
        bg.setColor(sf::Color(200, 200, 255, 200));
        bg.setPosition((float)width * 0.5f - texSize.x * 0.5f * scale, (float)height * 0.5f - texSize.y * 0.5f * scale);
        window.draw(bg);
    }

    sf::RectangleShape overlay(sf::Vector2f((float)width, (float)height));
    overlay.setFillColor(sf::Color(4, 8, 24, 200));
    window.draw(overlay);

    sf::Text header("Theme Studio", font, 40);
    header.setFillColor(sf::Color(255, 255, 240));
    header.setPosition(ui.sx(80.0f), ui.sy(80.0f));
    window.draw(header);

    sf::Text desc("Select a palette to recolor every panel, control, and trajectory.", font, 20);
    desc.setFillColor(sf::Color(200, 210, 230));
    desc.setPosition(ui.sx(80.0f), ui.sy(140.0f));
    window.draw(desc);

    for (int i = 0; i < kThemeCount; ++i)
    {
        bool hovered = gThemeCardRects[i].contains(mousePos);
        bool selected = (i == gCurrentThemeIndex);
        drawThemeCard(window, gThemeCardRects[i], gThemeDefinitions[i], selected, hovered, font, timeSeconds);
    }

    drawMenuButton(window, gSettingsBackRect, font, "Back", "Return to main menu", gSettingsBackRect.contains(mousePos), 0.3f);
    drawMusicToggleControl(window, font, mousePos);
}

static SearchResult runPathfinding(int startIndex, int endIndex, RouteSearchMode mode, const char *desiredDate, const char *desiredTime, bool enforcePreference, int excludedPort = -1)
{
    SearchResult result;
    if (startIndex < 0 || startIndex >= globalGraph.totalPorts)
        return result;
    if (endIndex < 0 || endIndex >= globalGraph.totalPorts)
        return result;
    if (excludedPort >= 0 && (excludedPort == startIndex || excludedPort == endIndex))
    {
        return result;
    }

    float dist[MAX_PORTS];
    int parent[MAX_PORTS];
    RouteEdge *parentEdge[MAX_PORTS];
    bool visited[MAX_PORTS];
    for (int i = 0; i < MAX_PORTS; ++i)
    {
        dist[i] = 1e12f;
        parent[i] = -1;
        parentEdge[i] = nullptr;
        visited[i] = false;
    }

    MinHeap<PathNode> heap(256, cmpPathNode);
    PathNode startNode;
    startNode.portIndex = startIndex;
    startNode.cost = 0.0f;
    startNode.heuristic = (mode == SearchFastest) ? (haversineDistance(startIndex, endIndex) / 30.0f) : 0.0f;
    startNode.parent = -1;
    startNode.parentEdge = nullptr;
    heap.push(startNode);
    dist[startIndex] = 0.0f;

    while (!heap.empty())
    {
        PathNode current = heap.pop();
        int u = current.portIndex;
        if (visited[u])
            continue;
        visited[u] = true;
        if (u == endIndex)
            break;
        AdjacencyNode *adj = globalGraph.adjacency[u];
        while (adj)
        {
            RouteEdge *edge = adj->edge;
            int v = edge->destIndex;
            if (excludedPort >= 0 && (v == excludedPort || u == excludedPort))
            {
                adj = adj->next;
                continue;
            }
            if (!companyAllowed(edge->companyName, enforcePreference))
            {
                adj = adj->next;
                continue;
            }
            if (u == startIndex && parent[u] == -1)
            {
                if (!matchesFirstLegSchedule(edge, desiredDate, desiredTime))
                {
                    adj = adj->next;
                    continue;
                }
            }
            float weight = (mode == SearchCheapest) ? (float)edge->costUSD : edge->durationHours;
            float newCost = dist[u] + weight;
            if (newCost < dist[v])
            {
                dist[v] = newCost;
                parent[v] = u;
                parentEdge[v] = edge;
                PathNode nextNode;
                nextNode.portIndex = v;
                nextNode.cost = newCost;
                nextNode.parent = u;
                nextNode.parentEdge = edge;
                nextNode.heuristic = (mode == SearchFastest) ? (haversineDistance(v, endIndex) / 30.0f) : 0.0f;
                heap.push(nextNode);
            }
            adj = adj->next;
        }
    }

    if (!visited[endIndex])
    {
        result.found = false;
        return result;
    }

    result.found = true;
    float sumCost = 0.0f;
    CustomStack<RouteEdge *> stack;
    int current = endIndex;
    while (current != -1 && parentEdge[current])
    {
        stack.push(parentEdge[current]);
        current = parent[current];
    }
    while (!stack.empty())
    {
        RouteEdge *re = stack.top();
        stack.pop();
        result.routeEdges.push_back(re);
        result.totalTime += re->durationHours;
        sumCost += (float)re->costUSD;
    }
    result.totalCost = sumCost;
    return result;
}

static RoutePlan buildRoutePlan(const SearchResult &route, RouteSearchMode mode, const char *desiredDate, const char *desiredTime, bool preferenceSatisfied)
{
    RoutePlan plan;
    plan.baseResult = route;
    plan.mode = mode;
    plan.preferenceSatisfied = preferenceSatisfied;
    if (desiredDate && desiredDate[0] != '\0')
    {
        std::strncpy(plan.requestedDate, desiredDate, 15);
        plan.requestedDate[15] = '\0';
    }
    else if (route.routeEdges.size > 0)
    {
        std::strncpy(plan.requestedDate, route.routeEdges[0]->departureDate, 15);
        plan.requestedDate[15] = '\0';
    }
    if (desiredTime && desiredTime[0] != '\0')
    {
        std::strncpy(plan.requestedTime, desiredTime, 15);
        plan.requestedTime[15] = '\0';
    }
    else if (route.routeEdges.size > 0)
    {
        std::strncpy(plan.requestedTime, route.routeEdges[0]->departureTime, 15);
        plan.requestedTime[15] = '\0';
    }
    plan.isDirect = (route.routeEdges.size == 1);
    if (!route.found || route.routeEdges.size == 0)
    {
        plan.visible = false;
        plan.realisticCost = 0.0f;
        plan.realisticTime = 0.0f;
        return plan;
    }

    float startHours = route.routeEdges[0]->departureHours;
    if (desiredDate && desiredTime && desiredDate[0] != '\0' && desiredTime[0] != '\0')
    {
        startHours = parseDateTimeHours(desiredDate, desiredTime);
    }
    plan.requestedStartHours = startHours;
    plan.simulatedLegs.clear();

    float runningCost = route.totalCost;
    float currentTime = startHours;
    for (int i = 0; i < route.routeEdges.size; ++i)
    {
        RouteEdge *edge = route.routeEdges[i];
        LegSimulation leg;
        leg.edge = edge;
        leg.plannedDepartureHours = edge->departureHours;
        leg.plannedArrivalHours = edge->arrivalHours;
        float actualDepart = maxValue(currentTime, edge->departureHours);
        float travelDuration = edge->durationHours;
        if (travelDuration <= 0.0f)
            travelDuration = 0.5f;
        leg.actualDepartureHours = actualDepart;
        leg.actualArrivalHours = actualDepart + travelDuration;
        leg.waitHours = 0.0f;
        leg.extraCost = 0.0f;
        leg.missedConnection = false;
        plan.simulatedLegs.push_back(leg);
        LegSimulation &stored = plan.simulatedLegs[plan.simulatedLegs.size - 1];
        currentTime = stored.actualArrivalHours;

        ShipArrival arrival;
        arrival.shipId = gNextShipId++;
        arrival.requestedArrivalHours = stored.actualArrivalHours;
        arrival.handlingHours = MIN_HANDLING_HOURS;
        arrival.actualStartHours = stored.actualArrivalHours;
        arrival.actualDepartureHours = stored.actualArrivalHours + MIN_HANDLING_HOURS;
        std::strncpy(arrival.origin, globalGraph.ports[edge->originIndex].name, MAX_NAME_LEN - 1);
        arrival.origin[MAX_NAME_LEN - 1] = '\0';
        std::strncpy(arrival.destination, globalGraph.ports[edge->destIndex].name, MAX_NAME_LEN - 1);
        arrival.destination[MAX_NAME_LEN - 1] = '\0';

        float extraCost = 0.0f;
        float waitHours = 0.0f;
        cleanupPortQueue(globalGraph.ports[edge->destIndex], currentTime - 168.0f);
        ShipArrival resolved = simulateDockingForPort(edge->destIndex, arrival, extraCost, waitHours);
        stored.extraCost += extraCost;
        stored.waitHours += waitHours;
        runningCost += extraCost;

        if (i < route.routeEdges.size - 1)
        {
            RouteEdge *nextEdge = route.routeEdges[i + 1];
            if (resolved.actualDepartureHours > nextEdge->departureHours + 0.01f)
            {
                stored.missedConnection = true;
            }
            currentTime = maxValue(resolved.actualDepartureHours, nextEdge->departureHours);
        }
        else
        {
            currentTime = resolved.actualDepartureHours;
        }
    }

    plan.realisticCost = runningCost;
    plan.realisticTime = currentTime - startHours;
    const char *modeLabel = (mode == SearchCheapest) ? "Cheapest" : "Fastest";
    const char *preferenceLabel = plan.preferenceSatisfied ? "" : " | Mixed carriers";
    std::snprintf(plan.summary, sizeof(plan.summary), "%s -> %s | %s | $%.0f | %.1f hrs%s",
                  globalGraph.ports[route.routeEdges[0]->originIndex].name,
                  globalGraph.ports[route.routeEdges[route.routeEdges.size - 1]->destIndex].name,
                  modeLabel,
                  plan.realisticCost,
                  plan.realisticTime,
                  preferenceLabel);
    return plan;
}

static bool routeHasIntermediateStops(const RoutePlan &plan)
{
    return plan.baseResult.routeEdges.size > 1;
}

static bool routeContainsIntermediatePort(const RoutePlan &plan, int portIndex)
{
    if (!routeHasIntermediateStops(plan))
        return false;
    if (plan.baseResult.routeEdges.size == 0)
        return false;
    int startPort = plan.baseResult.routeEdges[0]->originIndex;
    int endPort = plan.baseResult.routeEdges[plan.baseResult.routeEdges.size - 1]->destIndex;
    if (portIndex == startPort || portIndex == endPort)
        return false;
    for (int i = 0; i < plan.baseResult.routeEdges.size; ++i)
    {
        RouteEdge *edge = plan.baseResult.routeEdges[i];
        if (i > 0 && edge->originIndex == portIndex)
            return true;
        if (i < plan.baseResult.routeEdges.size - 1 && edge->destIndex == portIndex)
            return true;
    }
    return false;
}

static bool rebuildPlanExcludingPort(const RoutePlan &sourcePlan, int excludedPort, RoutePlan &outPlan)
{
    if (!routeHasIntermediateStops(sourcePlan))
        return false;
    if (!routeContainsIntermediatePort(sourcePlan, excludedPort))
        return false;
    int startPort = sourcePlan.baseResult.routeEdges[0]->originIndex;
    int endPort = sourcePlan.baseResult.routeEdges[sourcePlan.baseResult.routeEdges.size - 1]->destIndex;
    const char *dateFilter = (sourcePlan.requestedDate[0] != '\0') ? sourcePlan.requestedDate : nullptr;
    const char *timeFilter = (sourcePlan.requestedTime[0] != '\0') ? sourcePlan.requestedTime : nullptr;
    bool enforcePreference = sourcePlan.preferenceRequested;
    SearchResult attempt = runPathfinding(startPort, endPort, sourcePlan.mode, dateFilter, timeFilter, enforcePreference, excludedPort);
    bool satisfied = enforcePreference;
    if (!attempt.found)
    {
        satisfied = false;
        attempt = runPathfinding(startPort, endPort, sourcePlan.mode, dateFilter, timeFilter, false, excludedPort);
    }
    if (!attempt.found || attempt.routeEdges.size == 0)
    {
        return false;
    }
    outPlan = buildRoutePlan(attempt, sourcePlan.mode, dateFilter, timeFilter, satisfied);
    outPlan.preferenceRequested = sourcePlan.preferenceRequested;
    return true;
}

// ============================================================================
// Graphics + UI + Simulation
// ============================================================================
enum ButtonID
{
    ButtonFindCheapest,
    ButtonFindFastest,
    ButtonClear,
    ButtonShowRoutes,
    ButtonToggleDirect,
    ButtonToggleConnections,
    ButtonCount
};

struct UIButton
{
    sf::FloatRect bounds;
    std::string text;
    ButtonID id;
    bool hovered;
};

struct DropdownState
{
    bool expanded;
    int selectedIndex;
    int highlightIndex;
};

enum DropdownFocus
{
    FocusNone,
    FocusCompany,
    FocusDate,
    FocusTime
};

struct ShipAnimation
{
    bool active;
    float progress;
    float speed;
    DynamicArray<sf::Vector2f> points;
};

static sf::Vector2f computeCurvePoint(const sf::Vector2f &start, const sf::Vector2f &end, float t)
{
    float angle = std::sin(t * 3.14159f);
    sf::Vector2f mid = (start + end) * 0.5f;
    sf::Vector2f dir = end - start;
    sf::Vector2f normal(-dir.y, dir.x);
    float len = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (len > 0.0f)
        normal /= len;
    float curved = 80.0f * angle;
    sf::Vector2f point = (1 - t) * (1 - t) * start + 2 * (1 - t) * t * mid + t * t * end;
    point += normal * curved;
    return point;
}

static void buildRouteCurve(const SearchResult &route, ShipAnimation &anim, float mapWidth, float mapHeight)
{
    anim.points.clear();
    anim.active = false;
    anim.progress = 0.0f;
    anim.speed = 0.0008f;
    if (!route.found || route.routeEdges.size == 0)
        return;
    for (int i = 0; i < route.routeEdges.size; ++i)
    {
        RouteEdge *edge = route.routeEdges[i];
        Port &origin = globalGraph.ports[edge->originIndex];
        Port &dest = globalGraph.ports[edge->destIndex];
        sf::Vector2f start = mapLatLonToXY(origin.longitude, origin.latitude, mapWidth, mapHeight);
        sf::Vector2f end = mapLatLonToXY(dest.longitude, dest.latitude, mapWidth, mapHeight);
        int segments = 16;
        for (int s = 0; s <= segments; ++s)
        {
            float t = (float)s / (float)segments;
            sf::Vector2f point = computeCurvePoint(start, end, t);
            anim.points.push_back(point);
        }
    }
    anim.active = (anim.points.size > 1);
}

// ============================================================================
// Boat simulation update
// ============================================================================
static void updateBoats(float deltaTime, float mapWidth, float mapHeight, float zoomLevel, sf::Vector2f viewOffset)
{
    for (int b = 0; b < gActiveBoats.size; ++b)
    {
        AnimatedBoat &boat = gActiveBoats[b];
        if (!boat.active)
            continue;
        if (boat.routePlanIndex < 0 || boat.routePlanIndex >= gPlannedRoutes.size)
        {
            boat.active = false;
            continue;
        }
        RoutePlan &plan = gPlannedRoutes[boat.routePlanIndex];
        plan.isRunning = true;
        plan.hasLaunched = true;
        plan.isCompleted = false;
        if (boat.currentLegIndex >= plan.simulatedLegs.size)
        {
            boat.state = BoatCompleted;
            boat.active = false;
            plan.isRunning = false;
            plan.isCompleted = true;
            plan.runningProgress = 1.0f;
            continue;
        }

        boat.frameTime += deltaTime;
        if (boat.frameTime >= BOAT_FRAME_DURATION)
        {
            boat.frameTime -= BOAT_FRAME_DURATION;
            boat.currentFrame = (boat.currentFrame + 1) % BOAT_SPRITE_COLS;
        }

        LegSimulation &leg = plan.simulatedLegs[boat.currentLegIndex];
        RouteEdge *edge = leg.edge;
        if (!edge)
        {
            boat.active = false;
            plan.isRunning = false;
            plan.isCompleted = true;
            plan.runningProgress = 1.0f;
            continue;
        }

        Port &origin = globalGraph.ports[edge->originIndex];
        Port &dest = globalGraph.ports[edge->destIndex];

        if (boat.state == BoatTraveling)
        {
            float legDuration = leg.actualArrivalHours - leg.actualDepartureHours;
            if (legDuration <= 0)
                legDuration = 1.0f;
            boat.progress += (deltaTime * BOAT_SPEED_MULTIPLIER) / legDuration;

            if (boat.progress >= 1.0f)
            {
                boat.progress = 1.0f;
                boat.state = BoatWaitingInQueue;
                boat.waitStartTime = boat.simulationTime;
            }

            sf::Vector2f start = mapLatLonToXY(origin.longitude, origin.latitude, mapWidth, mapHeight);
            sf::Vector2f end = mapLatLonToXY(dest.longitude, dest.latitude, mapWidth, mapHeight);
            boat.position = start * (1.0f - boat.progress) + end * boat.progress;

            sf::Vector2f dir = end - start;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len > 0.0f)
            {
                boat.currentAngle = std::atan2(dir.y, dir.x) * 180.0f / 3.14159f;
            }
        }
        else if (boat.state == BoatWaitingInQueue)
        {
            float waitTime = leg.waitHours;
            if (boat.simulationTime - boat.waitStartTime >= waitTime)
            {
                boat.state = BoatAtDock;
                boat.dockingStartTime = boat.simulationTime;
            }
            sf::Vector2f destPos = mapLatLonToXY(dest.longitude, dest.latitude, mapWidth, mapHeight);
            boat.position = destPos;
        }
        else if (boat.state == BoatAtDock)
        {
            float handlingTime = MIN_HANDLING_HOURS;
            if (boat.simulationTime - boat.dockingStartTime >= handlingTime / 10.0f)
            {
                boat.currentLegIndex++;
                if (boat.currentLegIndex >= plan.simulatedLegs.size)
                {
                    boat.state = BoatCompleted;
                    boat.active = false;
                    plan.isRunning = false;
                    plan.isCompleted = true;
                    plan.runningProgress = 1.0f;
                }
                else
                {
                    boat.state = BoatTraveling;
                    boat.progress = 0.0f;
                }
            }
            sf::Vector2f destPos = mapLatLonToXY(dest.longitude, dest.latitude, mapWidth, mapHeight);
            boat.position = destPos;
        }

        float completedLegs = (float)boat.currentLegIndex;
        if (plan.simulatedLegs.size > 0)
        {
            if (boat.state == BoatTraveling)
            {
                completedLegs += clampValue(boat.progress, 0.0f, 1.0f);
            }
            else if (boat.state == BoatWaitingInQueue || boat.state == BoatAtDock)
            {
                completedLegs += 1.0f;
            }
            float divisor = (float)maxValue(1, plan.simulatedLegs.size);
            plan.runningProgress = minValue(1.0f, maxValue(0.0f, completedLegs / divisor));
        }
        else
        {
            plan.runningProgress = 1.0f;
        }

        boat.simulationTime += deltaTime;
    }

    for (int i = gActiveBoats.size - 1; i >= 0; --i)
    {
        if (!gActiveBoats[i].active)
        {
            if (gActiveBoats[i].routePlanIndex >= 0 && gActiveBoats[i].routePlanIndex < gPlannedRoutes.size)
            {
                RoutePlan &plan = gPlannedRoutes[gActiveBoats[i].routePlanIndex];
                if (plan.isRunning)
                {
                    plan.isRunning = false;
                    if (!plan.isCompleted)
                    {
                        plan.runningProgress = 0.0f;
                    }
                }
            }
            for (int j = i; j < gActiveBoats.size - 1; ++j)
            {
                gActiveBoats[j] = gActiveBoats[j + 1];
            }
            gActiveBoats.size--;
        }
    }
}

// ============================================================================
// Main
// ============================================================================
int main()
{
    parsePortCharges("PortCharges.txt");
    parseRoutes("Routes.txt");
    ensureDefaultRouteOptions();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int maxWidth = desktop.width > 60 ? desktop.width - 40u : desktop.width;
    unsigned int maxHeight = desktop.height > 80 ? desktop.height - 60u : desktop.height;
    unsigned int desiredWidth = minValue(1366u, maxWidth);
    unsigned int desiredHeight = minValue(768u, maxHeight);
    if (desiredWidth < 1200u && maxWidth >= 1200u)
        desiredWidth = 1200u;
    if (desiredHeight < 720u && maxHeight >= 720u)
        desiredHeight = 720u;
    sf::RenderWindow window(sf::VideoMode(desiredWidth, desiredHeight), "Maritime Route Navigator");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("./assets/title.ttf"))
    {
        font.loadFromFile("./assets/title.ttf");
    }

    sf::Texture mapTexture;
    bool hasMapTexture = mapTexture.loadFromFile("./assets/map.png");

    sf::Texture boatEastTexture, boatNorthTexture, boatSouthTexture, boatWestTexture;
    bool hasBoatEast = boatEastTexture.loadFromFile("./assets/east.png");
    bool hasBoatNorth = boatNorthTexture.loadFromFile("./assets/north.png");
    bool hasBoatSouth = boatSouthTexture.loadFromFile("./assets/south.png");
    bool hasBoatWest = boatWestTexture.loadFromFile("./assets/west.png");
    bool hasBoatTextures = hasBoatEast && hasBoatNorth && hasBoatSouth && hasBoatWest;
    if (!hasBoatTextures)
    {
        std::cout << "Warning: Could not load all boat direction PNGs" << std::endl;
    }

    gMenuTextureLoaded = gMenuTexture.loadFromFile("./assets/menu.png");
    if (!gMenuTextureLoaded)
    {
        std::cout << "Warning: menu.png missing; menu will use solid gradient." << std::endl;
    }

    if (gBackgroundMusic.openFromFile("./assets/music.wav"))
    {
        gMusicAvailable = true;
        setMusicState(true);
    }
    else
    {
        gMusicAvailable = false;
        gMusicEnabled = false;
        std::cout << "Warning: music.wav missing; background score disabled." << std::endl;
    }

    gThemeCardRects.resize(kThemeCount);

    UIManager ui;

    DropdownState dateDropdown = {false, gAvailableDates.size > 0 ? 0 : -1, gAvailableDates.size > 0 ? 0 : -1};
    DropdownState timeDropdown = {false, gAvailableTimes.size > 0 ? 0 : -1, gAvailableTimes.size > 0 ? 0 : -1};

    bool companyDropdownExpanded = false;
    bool showCompanyWarning = false;
    bool showTooltip = false;
    bool showEdgeTooltip = false;
    std::string tooltipText;
    std::string edgeTooltipText;
    sf::Vector2f tooltipPosition;
    sf::Vector2f edgeTooltipPosition;
    DropdownFocus dropdownFocus = FocusNone;
    int companyHighlightIndex = 0;

    int hoveredPortIndex = -1;
    int selectedOriginIndex = -1;
    int selectedDestinationIndex = -1;
    int highlightedRouteIndex = -1;
    bool awaitingNodeRemoval = false;
    int removalPlanIndex = -1;

    bool dragging = false;
    sf::Vector2f dragStart;
    sf::Vector2f viewOffset(0.0f, 0.0f);
    float zoomLevel = 1.3f;
    bool viewInitialized = false;
    bool showRouteOverlay = false;
    RouteDisplayFilter displayFilter = DisplayAllRoutes;

    sf::Clock clock;
    float deltaTime = 0.0f;
    sf::Clock menuClock;
    std::string actionMessage;
    float actionMessageTimer = 0.0f;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (actionMessageTimer > 0.0f)
        {
            actionMessageTimer = maxValue(0.0f, actionMessageTimer - deltaTime);
        }

        float targetPanel = sidePanelOpen ? 1.0f : 0.0f;
        float animSpeed = 8.0f;
        sidePanelAnim += (targetPanel - sidePanelAnim) * minValue(1.0f, deltaTime * animSpeed);

        float navTarget = gNavPanelOpen ? 1.0f : 0.0f;
        gNavPanelAnim += (navTarget - gNavPanelAnim) * minValue(1.0f, deltaTime * animSpeed);
        gNavPanelAnim = clampValue(gNavPanelAnim, 0.0f, 1.0f);
        if (!gNavPanelOpen && gNavPanelAnim < 0.05f)
        {
            companyDropdownExpanded = false;
            dateDropdown.expanded = false;
            timeDropdown.expanded = false;
            dropdownFocus = FocusNone;
        }

        sf::Vector2i mousePosScreen = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos((float)mousePosScreen.x, (float)mousePosScreen.y);

        sf::Vector2u winSize = window.getSize();
        ui.beginFrame(winSize);
        unsigned int currentWidth = winSize.x;
        unsigned int currentHeight = winSize.y;

        layoutMenu(ui, currentWidth, currentHeight);

        float mapWidth = (float)currentWidth;
        float mapHeight = (float)currentHeight;

        float panelWidth = clampValue((float)currentWidth * 0.26f, ui.sx(280.0f), ui.sx(360.0f));
        float panelMargin = ui.sx(28.0f);
        float panelBaseX = maxValue(panelMargin, (float)currentWidth - panelWidth - panelMargin);
        float panelCollapsedOffset = panelWidth + ui.sx(48.0f);
        float panelX = panelBaseX + (1.0f - gNavPanelAnim) * panelCollapsedOffset;
        float panelLeft = panelX + ui.sx(24.0f);
        float buttonWidth = panelWidth - ui.sx(48.0f);
        buttonWidth = maxValue(buttonWidth, ui.sx(220.0f));
        float buttonLeft = panelLeft;
        bool navPanelVisible = gNavPanelAnim > 0.05f;
        if (!viewInitialized)
        {
            viewOffset.x = 0.5f * (mapWidth - mapWidth * zoomLevel);
            viewOffset.y = 0.5f * (mapHeight - mapHeight * zoomLevel);
            viewInitialized = true;
        }
        clampViewToMap(viewOffset, zoomLevel, mapWidth, mapHeight);

        updateBoats(deltaTime, mapWidth, mapHeight, zoomLevel, viewOffset);

        const float dropdownHeight = ui.sy(46.0f);
        const float dropdownSpacing = ui.sy(16.0f);

        float controlsTop = ui.sy(140.0f);
        sf::FloatRect companyDropdownRect(buttonLeft, controlsTop, buttonWidth, dropdownHeight);
        sf::FloatRect dateDropdownRect(buttonLeft, companyDropdownRect.top + dropdownHeight + dropdownSpacing, buttonWidth, dropdownHeight);
        sf::FloatRect timeDropdownRect(buttonLeft, dateDropdownRect.top + dropdownHeight + dropdownSpacing, buttonWidth, dropdownHeight);

        UIButton buttons[ButtonCount];
        const float buttonHeight = ui.sy(54.0f);
        const float buttonSpacing = ui.sy(16.0f);
        float buttonY = timeDropdownRect.top + dropdownHeight + ui.sy(28.0f);
        buttons[ButtonFindCheapest].bounds = sf::FloatRect(buttonLeft, buttonY, buttonWidth, buttonHeight);
        buttons[ButtonFindCheapest].text = "Plan Cheapest";
        buttons[ButtonFindCheapest].id = ButtonFindCheapest;
        buttons[ButtonFindCheapest].hovered = false;

        buttonY += buttonHeight + buttonSpacing;
        buttons[ButtonFindFastest].bounds = sf::FloatRect(buttonLeft, buttonY, buttonWidth, buttonHeight);
        buttons[ButtonFindFastest].text = "Plan Fastest";
        buttons[ButtonFindFastest].id = ButtonFindFastest;
        buttons[ButtonFindFastest].hovered = false;

        buttonY += buttonHeight + buttonSpacing;
        buttons[ButtonClear].bounds = sf::FloatRect(buttonLeft, buttonY, buttonWidth, buttonHeight);
        buttons[ButtonClear].text = "Clear Selection";
        buttons[ButtonClear].id = ButtonClear;
        buttons[ButtonClear].hovered = false;

        buttonY += buttonHeight + buttonSpacing;
        buttons[ButtonShowRoutes].bounds = sf::FloatRect(buttonLeft, buttonY, buttonWidth, buttonHeight);
        buttons[ButtonShowRoutes].text = "Show Route Overlay";
        buttons[ButtonShowRoutes].id = ButtonShowRoutes;
        buttons[ButtonShowRoutes].hovered = false;

        buttonY += buttonHeight + buttonSpacing;
        float toggleWidth = (buttonWidth - ui.sx(12.0f)) * 0.5f;
        const float toggleHeight = ui.sy(46.0f);
        buttons[ButtonToggleDirect].bounds = sf::FloatRect(buttonLeft, buttonY, toggleWidth, toggleHeight);
        buttons[ButtonToggleDirect].text = "Direct";
        buttons[ButtonToggleDirect].id = ButtonToggleDirect;
        buttons[ButtonToggleDirect].hovered = false;

        buttons[ButtonToggleConnections].bounds = sf::FloatRect(buttonLeft + toggleWidth + ui.sx(12.0f), buttonY, toggleWidth, toggleHeight);
        buttons[ButtonToggleConnections].text = "Connecting";
        buttons[ButtonToggleConnections].id = ButtonToggleConnections;
        buttons[ButtonToggleConnections].hovered = false;

        buttonY += toggleHeight + buttonSpacing;
        UIButton removeButton;
        removeButton.text = "Remove Port";
        removeButton.hovered = false;
        removeButton.id = ButtonCount;
        removeButton.bounds = sf::FloatRect(buttonLeft, buttonY, buttonWidth, buttonHeight);
        bool removeButtonVisible = false;
        if (highlightedRouteIndex >= 0 && highlightedRouteIndex < gPlannedRoutes.size)
        {
            RoutePlan &selectedPlan = gPlannedRoutes[highlightedRouteIndex];
            if (!selectedPlan.hasLaunched && routeHasIntermediateStops(selectedPlan))
            {
                removeButtonVisible = true;
            }
        }
        if (!removeButtonVisible && awaitingNodeRemoval)
        {
            awaitingNodeRemoval = false;
            removalPlanIndex = -1;
        }

        const float sidePanelWidth = ui.sx(380.0f);
        const float sidePanelPadding = ui.sx(12.0f);
        const float plannedRowHeight = ui.sy(68.0f);
        const float plannedRowSpacing = ui.sy(80.0f);
        const float startButtonWidth = ui.sx(90.0f);
        const float sidePanelTop = ui.sy(70.0f);
        const float sidePanelX = -sidePanelWidth * (1.0f - sidePanelAnim);
        const float plannedListStartY = sidePanelTop + ui.sy(32.0f);
        float nextPlannedY = plannedListStartY;
        gRouteItemRects.clear();
        gRouteItemPlanOrder.clear();
        if (sidePanelAnim > 0.01f)
        {
            for (int i = 0; i < gPlannedRoutes.size; ++i)
            {
                if (gPlannedRoutes[i].isRunning)
                    continue;
                gRouteItemRects.push_back(sf::FloatRect(sidePanelX + sidePanelPadding, nextPlannedY, sidePanelWidth - sidePanelPadding * 2.0f, plannedRowHeight));
                gRouteItemPlanOrder.push_back(i);
                nextPlannedY += plannedRowSpacing;
            }
        }
        float plannedListEndY = (gRouteItemRects.size > 0)
                                    ? (gRouteItemRects[gRouteItemRects.size - 1].top + plannedRowHeight)
                                    : plannedListStartY;
        float runningSectionTop = plannedListEndY + ui.sy(32.0f);
        sf::FloatRect detailsBtnRect(ui.sx(12.0f), ui.sy(12.0f), ui.sx(130.0f), ui.sy(36.0f));
        sf::FloatRect navClampBtnRect(detailsBtnRect.left + detailsBtnRect.width + ui.sx(12.0f), detailsBtnRect.top, ui.sx(160.0f), ui.sy(36.0f));
        sf::FloatRect backToMenuRect(navClampBtnRect.left + navClampBtnRect.width + ui.sx(12.0f), detailsBtnRect.top, ui.sx(160.0f), ui.sy(36.0f));
        sf::FloatRect sideCloseRect(sidePanelX + sidePanelWidth - ui.sx(40.0f), sidePanelTop + ui.sy(8.0f), ui.sx(28.0f), ui.sy(28.0f));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                continue;
            }

            if (gAppScreen == AppScreen::Menu)
            {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                    if (gMenuStartRect.contains(mousePos))
                    {
                        gAppScreen = AppScreen::Simulation;
                        actionMessage = "Bridge consoles online.";
                        actionMessageTimer = 3.0f;
                    }
                    else if (gMenuSettingsRect.contains(mousePos))
                    {
                        gAppScreen = AppScreen::ThemeSettings;
                    }
                    else if (gMenuExitRect.contains(mousePos))
                    {
                        window.close();
                    }
                    else if (gMusicToggleRect.contains(mousePos))
                    {
                        toggleMusic();
                    }
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                continue;
            }

            if (gAppScreen == AppScreen::ThemeSettings)
            {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                    if (gSettingsBackRect.contains(mousePos))
                    {
                        gAppScreen = AppScreen::Menu;
                    }
                    else if (gMusicToggleRect.contains(mousePos))
                    {
                        toggleMusic();
                    }
                    else
                    {
                        for (int i = 0; i < kThemeCount; ++i)
                        {
                            if (gThemeCardRects[i].contains(mousePos))
                            {
                                applyTheme(i);
                                actionMessage = std::string("Applied ") + gThemeDefinitions[i].name;
                                actionMessageTimer = 3.5f;
                                break;
                            }
                        }
                    }
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    gAppScreen = AppScreen::Menu;
                }
                continue;
            }

            switch (event.type)
            {
            case sf::Event::MouseWheelScrolled:
            {
                float oldZoom = zoomLevel;
                if (event.mouseWheelScroll.delta > 0)
                    zoomLevel *= 1.1f;
                else
                    zoomLevel *= 0.9f;
                zoomLevel = maxValue(0.5f, minValue(3.0f, zoomLevel));
                sf::Vector2f mouseWorld = (mousePos - viewOffset) / oldZoom;
                viewOffset = mousePos - mouseWorld * zoomLevel;
                clampViewToMap(viewOffset, zoomLevel, mapWidth, mapHeight);
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                    bool insidePrimaryPanel = navPanelVisible && (mousePos.x >= panelX && mousePos.x <= panelX + panelWidth && mousePos.y >= 0.0f && mousePos.y <= (float)currentHeight);
                    if (!insidePrimaryPanel)
                    {
                        dragging = true;
                        dragStart = mousePos - viewOffset;
                    }
                    else
                    {
                        dragging = false;
                    }
                    if (companyDropdownRect.contains(mousePos))
                    {
                        companyDropdownExpanded = !companyDropdownExpanded;
                        if (companyDropdownExpanded)
                        {
                            dropdownFocus = FocusCompany;
                            if (gCompanyOptions.size > 0)
                            {
                                int selectedIdx = -1;
                                for (int i = 0; i < gCompanyOptions.size; ++i)
                                {
                                    if (gCompanyOptions[i].selected)
                                    {
                                        selectedIdx = i;
                                        break;
                                    }
                                }
                                if (selectedIdx >= 0)
                                    companyHighlightIndex = selectedIdx;
                                else if (companyHighlightIndex < 0 || companyHighlightIndex >= gCompanyOptions.size)
                                {
                                    companyHighlightIndex = 0;
                                }
                            }
                        }
                        else if (dropdownFocus == FocusCompany)
                        {
                            dropdownFocus = FocusNone;
                        }
                    }
                    else if (!companyDropdownRect.contains(mousePos))
                    {
                        if (companyDropdownExpanded)
                        {
                            companyDropdownExpanded = false;
                            if (dropdownFocus == FocusCompany)
                                dropdownFocus = FocusNone;
                        }
                    }
                    if (dateDropdownRect.contains(mousePos))
                    {
                        dateDropdown.expanded = !dateDropdown.expanded;
                        if (dateDropdown.expanded)
                        {
                            dropdownFocus = FocusDate;
                            if (dateDropdown.highlightIndex < 0 && gAvailableDates.size > 0)
                                dateDropdown.highlightIndex = 0;
                            else if (dateDropdown.selectedIndex >= 0)
                                dateDropdown.highlightIndex = dateDropdown.selectedIndex;
                        }
                        else if (dropdownFocus == FocusDate)
                        {
                            dropdownFocus = FocusNone;
                        }
                    }
                    else if (!dateDropdownRect.contains(mousePos))
                    {
                        if (dateDropdown.expanded)
                        {
                            dateDropdown.expanded = false;
                            if (dropdownFocus == FocusDate)
                                dropdownFocus = FocusNone;
                        }
                    }
                    if (timeDropdownRect.contains(mousePos))
                    {
                        timeDropdown.expanded = !timeDropdown.expanded;
                        if (timeDropdown.expanded)
                        {
                            dropdownFocus = FocusTime;
                            if (timeDropdown.highlightIndex < 0 && gAvailableTimes.size > 0)
                                timeDropdown.highlightIndex = 0;
                            else if (timeDropdown.selectedIndex >= 0)
                                timeDropdown.highlightIndex = timeDropdown.selectedIndex;
                        }
                        else if (dropdownFocus == FocusTime)
                        {
                            dropdownFocus = FocusNone;
                        }
                    }
                    else if (!timeDropdownRect.contains(mousePos))
                    {
                        if (timeDropdown.expanded)
                        {
                            timeDropdown.expanded = false;
                            if (dropdownFocus == FocusTime)
                                dropdownFocus = FocusNone;
                        }
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                    dragging = false;
                    bool handled = false;
                    bool insidePrimaryPanel = navPanelVisible && (mousePos.x >= panelX && mousePos.x <= panelX + panelWidth && mousePos.y >= 0.0f && mousePos.y <= (float)currentHeight);
                    if (detailsBtnRect.contains(mousePos))
                    {
                        sidePanelOpen = !sidePanelOpen;
                        handled = true;
                    }
                    if (!handled && navClampBtnRect.contains(mousePos))
                    {
                        gNavPanelOpen = !gNavPanelOpen;
                        if (!gNavPanelOpen)
                        {
                            companyDropdownExpanded = false;
                            dateDropdown.expanded = false;
                            timeDropdown.expanded = false;
                            dropdownFocus = FocusNone;
                        }
                        handled = true;
                    }
                    if (!handled && backToMenuRect.contains(mousePos))
                    {
                        gAppScreen = AppScreen::Menu;
                        sidePanelOpen = false;
                        gNavPanelOpen = true;
                        handled = true;
                        break;
                    }
                    if (!handled && sidePanelAnim > 0.05f && sideCloseRect.contains(mousePos))
                    {
                        sidePanelOpen = false;
                        handled = true;
                    }
                    bool insideSidePanel = (sidePanelAnim > 0.05f) && (mousePos.x >= sidePanelX) && (mousePos.x <= sidePanelX + sidePanelWidth);

                    // Side panel interactions take priority over map clicks.
                    if (!handled && insideSidePanel)
                    {
                        for (int idx = 0; idx < gRouteItemRects.size; ++idx)
                        {
                            int planIndex = gRouteItemPlanOrder[idx];
                            if (planIndex < 0 || planIndex >= gPlannedRoutes.size)
                                continue;
                            RoutePlan &plan = gPlannedRoutes[planIndex];
                            if (plan.hasLaunched)
                                continue;
                            const sf::FloatRect &rowRect = gRouteItemRects[idx];
                            sf::FloatRect startBtnRect(rowRect.left + rowRect.width - startButtonWidth - ui.sx(8.0f),
                                                       rowRect.top + ui.sy(8.0f),
                                                       startButtonWidth,
                                                       rowRect.height - ui.sy(16.0f));
                            if (startBtnRect.contains(mousePos))
                            {
                                AnimatedBoat boat;
                                boat.routePlanIndex = planIndex;
                                boat.currentLegIndex = 0;
                                boat.state = BoatTraveling;
                                boat.progress = 0.0f;
                                boat.simulationTime = 0.0f;
                                boat.active = true;
                                gActiveBoats.push_back(boat);
                                plan.hasLaunched = true;
                                plan.isRunning = true;
                                plan.isCompleted = false;
                                plan.runningProgress = 0.0f;
                                awaitingNodeRemoval = false;
                                removalPlanIndex = -1;
                                actionMessage = "Route started!";
                                actionMessageTimer = 2.0f;
                                handled = true;
                                break;
                            }
                        }
                        if (!handled)
                        {
                            for (int idx = 0; idx < gRouteItemRects.size; ++idx)
                            {
                                if (gRouteItemRects[idx].contains(mousePos))
                                {
                                    if (idx >= 0 && idx < gRouteItemPlanOrder.size)
                                    {
                                        highlightedRouteIndex = gRouteItemPlanOrder[idx];
                                    }
                                    showRouteOverlay = true;
                                    awaitingNodeRemoval = false;
                                    removalPlanIndex = -1;
                                    handled = true;
                                    break;
                                }
                            }
                        }
                        // Swallow clicks inside the panel even if they missed controls.
                        if (!handled)
                            handled = true;
                    }
                    if (handled)
                        break;
                    if (!insidePrimaryPanel && !insideSidePanel)
                    {
                        hoveredPortIndex = -1;
                        int clickedPort = -1;
                        float bestDist = 9999.0f;
                        for (int i = 0; i < globalGraph.totalPorts; ++i)
                        {
                            Port &port = globalGraph.ports[i];
                            sf::Vector2f pos = mapLatLonToXY(port.longitude, port.latitude, mapWidth, mapHeight);
                            pos = pos * zoomLevel + viewOffset;
                            float dx = pos.x - mousePos.x;
                            float dy = pos.y - mousePos.y;
                            float dist = std::sqrt(dx * dx + dy * dy);
                            if (dist < 10.5f && dist < bestDist)
                            {
                                bestDist = dist;
                                hoveredPortIndex = i;
                                clickedPort = i;
                            }
                        }
                        if (clickedPort >= 0 && awaitingNodeRemoval && removalPlanIndex >= 0 && removalPlanIndex < gPlannedRoutes.size)
                        {
                            RoutePlan &targetPlan = gPlannedRoutes[removalPlanIndex];
                            handled = true;
                            if (!routeContainsIntermediatePort(targetPlan, clickedPort))
                            {
                                actionMessage = "Pick an intermediate port from the highlighted route.";
                                actionMessageTimer = 3.5f;
                            }
                            else
                            {
                                RoutePlan rebuilt;
                                if (rebuildPlanExcludingPort(targetPlan, clickedPort, rebuilt))
                                {
                                    gPlannedRoutes[removalPlanIndex] = rebuilt;
                                    highlightedRouteIndex = removalPlanIndex;
                                    awaitingNodeRemoval = false;
                                    removalPlanIndex = -1;
                                    showRouteOverlay = true;
                                    actionMessage = "Port removed. Route updated.";
                                    actionMessageTimer = 4.0f;
                                }
                                else
                                {
                                    actionMessage = "No alternate route available after removing that port.";
                                    actionMessageTimer = 4.0f;
                                }
                            }
                            break;
                        }
                        if (clickedPort >= 0 && !awaitingNodeRemoval)
                        {
                            if (selectedOriginIndex < 0)
                            {
                                selectedOriginIndex = clickedPort;
                                selectedDestinationIndex = -1;
                            }
                            else if (selectedDestinationIndex < 0)
                            {
                                if (clickedPort != selectedOriginIndex)
                                {
                                    selectedDestinationIndex = clickedPort;
                                }
                            }
                            else
                            {
                                selectedOriginIndex = clickedPort;
                                selectedDestinationIndex = -1;
                            }
                        }
                    }
                    else if (insidePrimaryPanel)
                    {
                        handled = false;
                        if (companyDropdownExpanded)
                        {
                            float entryY = companyDropdownRect.top + companyDropdownRect.height;
                            for (int i = 0; i < gCompanyOptions.size; ++i)
                            {
                                sf::FloatRect entryRect(companyDropdownRect.left, entryY + i * 34.0f, companyDropdownRect.width, 32.0f);
                                if (entryRect.contains(mousePos))
                                {
                                    companyHighlightIndex = i;
                                    exclusiveToggleCompany(i);
                                    showCompanyWarning = false;
                                    handled = true;
                                    break;
                                }
                            }
                            if (!companyDropdownRect.contains(mousePos) && !handled)
                            {
                                companyDropdownExpanded = false;
                            }
                            if (handled)
                                break;
                        }
                        if (dateDropdown.expanded)
                        {
                            float entryY = dateDropdownRect.top + dateDropdownRect.height;
                            for (int i = 0; i < gAvailableDates.size; ++i)
                            {
                                sf::FloatRect entryRect(dateDropdownRect.left, entryY + i * 32.0f, dateDropdownRect.width, 30.0f);
                                if (entryRect.contains(mousePos))
                                {
                                    dateDropdown.selectedIndex = i;
                                    dateDropdown.highlightIndex = i;
                                    dateDropdown.expanded = false;
                                    if (dropdownFocus == FocusDate)
                                        dropdownFocus = FocusNone;
                                }
                            }
                        }
                        if (timeDropdown.expanded)
                        {
                            float entryY = timeDropdownRect.top + timeDropdownRect.height;
                            for (int i = 0; i < gAvailableTimes.size; ++i)
                            {
                                sf::FloatRect entryRect(timeDropdownRect.left, entryY + i * 32.0f, timeDropdownRect.width, 30.0f);
                                if (entryRect.contains(mousePos))
                                {
                                    timeDropdown.selectedIndex = i;
                                    timeDropdown.highlightIndex = i;
                                    timeDropdown.expanded = false;
                                    if (dropdownFocus == FocusTime)
                                        dropdownFocus = FocusNone;
                                }
                            }
                        }
                        for (int i = 0; i < ButtonCount; ++i)
                        {
                            if (buttons[i].bounds.contains(mousePos))
                            {
                                handled = true;
                                switch (buttons[i].id)
                                {
                                case ButtonFindCheapest:
                                case ButtonFindFastest:
                                {
                                    if (!hasCompanyPreference())
                                    {
                                        showCompanyWarning = true;
                                        actionMessage = "Select preferred companies before planning.";
                                        actionMessageTimer = 4.0f;
                                        break;
                                    }
                                    if (selectedOriginIndex < 0 || selectedDestinationIndex < 0)
                                    {
                                        actionMessage = "Select both origin and destination ports.";
                                        actionMessageTimer = 4.0f;
                                        break;
                                    }
                                    RouteSearchMode mode = (buttons[i].id == ButtonFindCheapest) ? SearchCheapest : SearchFastest;
                                    std::string dateValue = (dateDropdown.selectedIndex >= 0 && dateDropdown.selectedIndex < gAvailableDates.size) ? gAvailableDates[dateDropdown.selectedIndex] : std::string("Any");
                                    std::string timeValue = (timeDropdown.selectedIndex >= 0 && timeDropdown.selectedIndex < gAvailableTimes.size) ? gAvailableTimes[timeDropdown.selectedIndex] : std::string("Any");
                                    const char *dateFilter = (dateValue == "Any") ? nullptr : dateValue.c_str();
                                    const char *timeFilter = (timeValue == "Any") ? nullptr : timeValue.c_str();
                                    bool enforcePreference = hasCompanyPreference();
                                    SearchResult preferred = runPathfinding(selectedOriginIndex, selectedDestinationIndex, mode, dateFilter, timeFilter, enforcePreference);
                                    bool preferenceSatisfied = (!enforcePreference) || preferred.found;
                                    SearchResult finalResult = preferred;
                                    if (!preferred.found)
                                    {
                                        finalResult = runPathfinding(selectedOriginIndex, selectedDestinationIndex, mode, dateFilter, timeFilter, false);
                                    }
                                    if (!finalResult.found)
                                    {
                                        actionMessage = "No feasible route for selected criteria.";
                                        actionMessageTimer = 4.0f;
                                        break;
                                    }
                                    RoutePlan plan = buildRoutePlan(finalResult, mode, dateFilter, timeFilter, preferenceSatisfied);
                                    plan.preferenceRequested = enforcePreference;
                                    gPlannedRoutes.push_back(plan);
                                    highlightedRouteIndex = gPlannedRoutes.size - 1;
                                    awaitingNodeRemoval = false;
                                    removalPlanIndex = -1;
                                    showRouteOverlay = true;
                                    if (!preferenceSatisfied && enforcePreference)
                                    {
                                        actionMessage = "Preferred company unavailable; showing best alternative.";
                                        actionMessageTimer = 5.0f;
                                    }
                                    else
                                    {
                                        actionMessage = "Route added to itinerary.";
                                        actionMessageTimer = 4.0f;
                                    }
                                    break;
                                }
                                case ButtonClear:
                                    selectedOriginIndex = -1;
                                    selectedDestinationIndex = -1;
                                    gPlannedRoutes.clear();
                                    highlightedRouteIndex = -1;
                                    showRouteOverlay = false;
                                    awaitingNodeRemoval = false;
                                    removalPlanIndex = -1;
                                    actionMessage = "Selection cleared.";
                                    actionMessageTimer = 3.0f;
                                    break;
                                case ButtonShowRoutes:
                                    showRouteOverlay = !showRouteOverlay;
                                    break;
                                case ButtonToggleDirect:
                                    displayFilter = (displayFilter == DisplayDirectOnly) ? DisplayAllRoutes : DisplayDirectOnly;
                                    break;
                                case ButtonToggleConnections:
                                    displayFilter = (displayFilter == DisplayConnectingOnly) ? DisplayAllRoutes : DisplayConnectingOnly;
                                    break;
                                default:
                                    break;
                                }
                                break;
                            }
                        }
                        if (!handled && removeButtonVisible && removeButton.bounds.contains(mousePos))
                        {
                            handled = true;
                            if (awaitingNodeRemoval && removalPlanIndex == highlightedRouteIndex)
                            {
                                awaitingNodeRemoval = false;
                                removalPlanIndex = -1;
                                actionMessage = "Removal cancelled.";
                                actionMessageTimer = 3.0f;
                            }
                            else if (highlightedRouteIndex >= 0 && highlightedRouteIndex < gPlannedRoutes.size)
                            {
                                RoutePlan &plan = gPlannedRoutes[highlightedRouteIndex];
                                if (!plan.hasLaunched && routeHasIntermediateStops(plan))
                                {
                                    awaitingNodeRemoval = true;
                                    removalPlanIndex = highlightedRouteIndex;
                                    actionMessage = "Select an intermediate port on the map to remove.";
                                    actionMessageTimer = 4.0f;
                                }
                            }
                        }
                        if (!handled)
                        {
                            for (int idx = 0; idx < gRouteItemRects.size; ++idx)
                            {
                                int planIndex = gRouteItemPlanOrder[idx];
                                if (planIndex < 0 || planIndex >= gPlannedRoutes.size)
                                    continue;
                                RoutePlan &plan = gPlannedRoutes[planIndex];
                                if (plan.hasLaunched)
                                    continue;
                                const sf::FloatRect &rowRect = gRouteItemRects[idx];
                                sf::FloatRect startBtnRect(rowRect.left + rowRect.width - startButtonWidth - ui.sx(8.0f),
                                                           rowRect.top + ui.sy(8.0f),
                                                           startButtonWidth,
                                                           rowRect.height - ui.sy(16.0f));
                                if (startBtnRect.contains(mousePos))
                                {
                                    AnimatedBoat boat;
                                    boat.routePlanIndex = planIndex;
                                    boat.currentLegIndex = 0;
                                    boat.state = BoatTraveling;
                                    boat.progress = 0.0f;
                                    boat.simulationTime = 0.0f;
                                    boat.active = true;
                                    gActiveBoats.push_back(boat);
                                    plan.hasLaunched = true;
                                    plan.isRunning = true;
                                    plan.isCompleted = false;
                                    plan.runningProgress = 0.0f;
                                    actionMessage = "Route started!";
                                    actionMessageTimer = 2.0f;
                                    handled = true;
                                    break;
                                }
                            }
                        }
                        if (!handled)
                        {
                            for (int idx = 0; idx < gRouteItemRects.size; ++idx)
                            {
                                if (gRouteItemRects[idx].contains(mousePos))
                                {
                                    if (idx >= 0 && idx < gRouteItemPlanOrder.size)
                                    {
                                        highlightedRouteIndex = gRouteItemPlanOrder[idx];
                                    }
                                    showRouteOverlay = true;
                                    handled = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (companyDropdownExpanded || dateDropdown.expanded || timeDropdown.expanded)
                    {
                        companyDropdownExpanded = false;
                        dateDropdown.expanded = false;
                        timeDropdown.expanded = false;
                        dropdownFocus = FocusNone;
                    }
                    break;
                }
                bool handledKey = false;
                if (companyDropdownExpanded && dropdownFocus == FocusCompany && gCompanyOptions.size > 0)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        companyHighlightIndex = (companyHighlightIndex + 1) % gCompanyOptions.size;
                        handledKey = true;
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        companyHighlightIndex = (companyHighlightIndex - 1 + gCompanyOptions.size) % gCompanyOptions.size;
                        handledKey = true;
                    }
                    else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
                    {
                        exclusiveToggleCompany(companyHighlightIndex);
                        showCompanyWarning = false;
                        handledKey = true;
                    }
                }
                if (!handledKey && dateDropdown.expanded && dropdownFocus == FocusDate && gAvailableDates.size > 0)
                {
                    if (dateDropdown.highlightIndex < 0)
                        dateDropdown.highlightIndex = (dateDropdown.selectedIndex >= 0) ? dateDropdown.selectedIndex : 0;
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        dateDropdown.highlightIndex = (dateDropdown.highlightIndex + 1) % gAvailableDates.size;
                        handledKey = true;
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        dateDropdown.highlightIndex = (dateDropdown.highlightIndex - 1 + gAvailableDates.size) % gAvailableDates.size;
                        handledKey = true;
                    }
                    else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
                    {
                        dateDropdown.selectedIndex = dateDropdown.highlightIndex;
                        dateDropdown.expanded = false;
                        dropdownFocus = FocusNone;
                        handledKey = true;
                    }
                }
                if (!handledKey && timeDropdown.expanded && dropdownFocus == FocusTime && gAvailableTimes.size > 0)
                {
                    if (timeDropdown.highlightIndex < 0)
                        timeDropdown.highlightIndex = (timeDropdown.selectedIndex >= 0) ? timeDropdown.selectedIndex : 0;
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        timeDropdown.highlightIndex = (timeDropdown.highlightIndex + 1) % gAvailableTimes.size;
                        handledKey = true;
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        timeDropdown.highlightIndex = (timeDropdown.highlightIndex - 1 + gAvailableTimes.size) % gAvailableTimes.size;
                        handledKey = true;
                    }
                    else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
                    {
                        timeDropdown.selectedIndex = timeDropdown.highlightIndex;
                        timeDropdown.expanded = false;
                        dropdownFocus = FocusNone;
                        handledKey = true;
                    }
                }
                break;
            }
            case sf::Event::MouseMoved:
            {
                mousePos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
                bool insidePrimaryPanel = navPanelVisible && (mousePos.x >= panelX && mousePos.x <= panelX + panelWidth && mousePos.y >= 0.0f && mousePos.y <= (float)currentHeight);
                if (dragging)
                {
                    viewOffset = mousePos - dragStart;
                    clampViewToMap(viewOffset, zoomLevel, mapWidth, mapHeight);
                }
                showTooltip = false;
                hoveredPortIndex = -1;
                if (!insidePrimaryPanel)
                {
                    float bestDist = 9999.0f;
                    for (int i = 0; i < globalGraph.totalPorts; ++i)
                    {
                        Port &port = globalGraph.ports[i];
                        sf::Vector2f pos = mapLatLonToXY(port.longitude, port.latitude, mapWidth, mapHeight);
                        pos = pos * zoomLevel + viewOffset;
                        float dx = pos.x - mousePos.x;
                        float dy = pos.y - mousePos.y;
                        float dist = std::sqrt(dx * dx + dy * dy);
                        if (dist < 9.0f && dist < bestDist)
                        {
                            bestDist = dist;
                            hoveredPortIndex = i;
                        }
                    }
                    if (hoveredPortIndex >= 0)
                    {
                        showTooltip = true;
                        tooltipPosition = mousePos;
                        const Port &port = globalGraph.ports[hoveredPortIndex];
                        float waitEstimate = portQueueWaitEstimate(port);
                        char buf[192];
                        std::snprintf(buf, sizeof(buf), "%s\nCharge: %d USD/day\nQueue: %d ships | Wait ~%.1fh", port.name, port.chargePerDay, port.dockQueue.size(), waitEstimate);
                        tooltipText = buf;
                    }
                }
                break;
            }
            default:
                break;
            }
        }

        if (gAppScreen == AppScreen::Menu || gAppScreen == AppScreen::ThemeSettings)
        {
            float timeSeconds = menuClock.getElapsedTime().asSeconds();
            window.clear(sf::Color::Black);
            if (gAppScreen == AppScreen::Menu)
            {
                drawMainMenu(window, font, ui, currentWidth, currentHeight, mousePos, timeSeconds);
            }
            else
            {
                drawThemeSettings(window, font, ui, currentWidth, currentHeight, mousePos, timeSeconds);
            }
            window.display();
            continue;
        }

        for (int i = 0; i < ButtonCount; ++i)
        {
            buttons[i].hovered = navPanelVisible && buttons[i].bounds.contains(mousePos);
        }
        if (removeButtonVisible)
        {
            removeButton.hovered = navPanelVisible && removeButton.bounds.contains(mousePos);
        }

        gRenderableEdges.clear();
        window.clear(gThemePalette.windowClear);
        drawMapTextureLayer(window, hasMapTexture ? &mapTexture : nullptr, mapWidth, mapHeight, zoomLevel, viewOffset);
        drawCompassOverlay(window, mapWidth, font);
        drawScaleBar(window, mapWidth, (float)currentHeight, font, zoomLevel);

        if (showRouteOverlay)
        {
            if (gPlannedRoutes.size > 0)
            {
                for (int i = 0; i < gPlannedRoutes.size; ++i)
                {
                    RoutePlan &plan = gPlannedRoutes[i];
                    bool matchesFilter = (displayFilter == DisplayAllRoutes) ||
                                         (displayFilter == DisplayDirectOnly && plan.isDirect) ||
                                         (displayFilter == DisplayConnectingOnly && !plan.isDirect);
                    if (!plan.visible || !matchesFilter)
                        continue;
                    if (highlightedRouteIndex >= 0 && highlightedRouteIndex != i)
                        continue;
                    sf::Color bandColor = plan.isDirect ? sf::Color(255, 215, 0, 220) : sf::Color(80, 200, 255, 210);
                    sf::Color coreColor = plan.isDirect ? sf::Color(255, 255, 255, 230) : sf::Color(255, 255, 255, 180);
                    for (int legIndex = 0; legIndex < plan.simulatedLegs.size; ++legIndex)
                    {
                        const LegSimulation &leg = plan.simulatedLegs[legIndex];
                        Port &origin = globalGraph.ports[leg.edge->originIndex];
                        Port &dest = globalGraph.ports[leg.edge->destIndex];
                        sf::Vector2f start = mapLatLonToXY(origin.longitude, origin.latitude, mapWidth, mapHeight);
                        sf::Vector2f end = mapLatLonToXY(dest.longitude, dest.latitude, mapWidth, mapHeight);
                        start = start * zoomLevel + viewOffset;
                        end = end * zoomLevel + viewOffset;
                        sf::Vector2f diff = end - start;
                        float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                        if (length < 1.0f)
                            continue;
                        float angle = std::atan2(diff.y, diff.x) * 180.0f / (float)M_PI;
                        sf::RectangleShape pathBand(sf::Vector2f(length, 6.0f));
                        pathBand.setOrigin(0.0f, 3.0f);
                        pathBand.setPosition(start);
                        pathBand.setRotation(angle);
                        pathBand.setFillColor(bandColor);
                        window.draw(pathBand);
                        sf::RectangleShape core(sf::Vector2f(length, 2.5f));
                        core.setOrigin(0.0f, 1.25f);
                        core.setPosition(start);
                        core.setRotation(angle);
                        core.setFillColor(coreColor);
                        window.draw(core);
                        RenderedEdgeSegment segment;
                        segment.edge = leg.edge;
                        segment.start = start;
                        segment.end = end;
                        segment.actualDeparture = leg.actualDepartureHours;
                        segment.actualArrival = leg.actualArrivalHours;
                        segment.isDirect = plan.isDirect;
                        segment.legRef = &leg;
                        gRenderableEdges.push_back(segment);
                    }
                }
            }
            else
            {
                for (int i = 0; i < globalGraph.totalRoutes; ++i)
                {
                    RouteEdge *edge = &globalGraph.routes[i];
                    Port &origin = globalGraph.ports[edge->originIndex];
                    Port &dest = globalGraph.ports[edge->destIndex];
                    sf::Vector2f start = mapLatLonToXY(origin.longitude, origin.latitude, mapWidth, mapHeight);
                    sf::Vector2f end = mapLatLonToXY(dest.longitude, dest.latitude, mapWidth, mapHeight);
                    start = start * zoomLevel + viewOffset;
                    end = end * zoomLevel + viewOffset;
                    sf::Vector2f diff = end - start;
                    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                    if (length < 1.0f)
                        continue;
                    float angle = std::atan2(diff.y, diff.x) * 180.0f / (float)M_PI;
                    bool touchesSelection = (selectedOriginIndex >= 0 && (edge->originIndex == selectedOriginIndex || edge->destIndex == selectedOriginIndex)) ||
                                            (selectedDestinationIndex >= 0 && (edge->originIndex == selectedDestinationIndex || edge->destIndex == selectedDestinationIndex));
                    sf::Color baseColor = touchesSelection ? sf::Color(255, 200, 120, 200) : sf::Color(100, 140, 190, 130);
                    float thickness = touchesSelection ? 4.0f : 2.0f;
                    sf::RectangleShape line(sf::Vector2f(length, thickness));
                    line.setOrigin(0.0f, thickness * 0.5f);
                    line.setPosition(start);
                    line.setRotation(angle);
                    line.setFillColor(baseColor);
                    window.draw(line);
                    RenderedEdgeSegment segment;
                    segment.edge = edge;
                    segment.start = start;
                    segment.end = end;
                    segment.actualDeparture = edge->departureHours;
                    segment.actualArrival = edge->arrivalHours;
                    segment.isDirect = touchesSelection;
                    segment.legRef = nullptr;
                    gRenderableEdges.push_back(segment);
                }
            }
        }

        showEdgeTooltip = false;
        float bestEdgeDist = 18.0f;
        for (int i = 0; i < gRenderableEdges.size; ++i)
        {
            const RenderedEdgeSegment &seg = gRenderableEdges[i];
            float dist = distancePointToSegment(mousePos, seg.start, seg.end);
            if (dist < bestEdgeDist && seg.legRef)
            {
                bestEdgeDist = dist;
                const Port &origin = globalGraph.ports[seg.legRef->edge->originIndex];
                const Port &dest = globalGraph.ports[seg.legRef->edge->destIndex];
                float departDelay = seg.legRef->actualDepartureHours - seg.legRef->plannedDepartureHours;
                float arriveDelay = seg.legRef->actualArrivalHours - seg.legRef->plannedArrivalHours;
                char buf[256];
                std::snprintf(buf, sizeof(buf), "%s -> %s\n%s | %s to %s\nDepart delay %.1fh | Arrival delay %.1fh\nLayover %.1fh | Extra $%.0f",
                              origin.name,
                              dest.name,
                              seg.edge->companyName,
                              seg.edge->departureTime,
                              seg.edge->arrivalTime,
                              departDelay,
                              arriveDelay,
                              seg.legRef->waitHours,
                              seg.legRef->extraCost);
                edgeTooltipText = buf;
                edgeTooltipPosition = mousePos;
                showEdgeTooltip = true;
            }
        }

        for (int i = 0; i < globalGraph.totalPorts; ++i)
        {
            Port &port = globalGraph.ports[i];
            sf::Vector2f pos = mapLatLonToXY(port.longitude, port.latitude, mapWidth, mapHeight);
            pos = pos * zoomLevel + viewOffset;
            sf::CircleShape halo(14.0f);
            halo.setOrigin(14.0f, 14.0f);
            halo.setPosition(pos);
            halo.setFillColor(sf::Color(80, 190, 255, 45));
            window.draw(halo);
            sf::CircleShape circle(5.0f);
            circle.setPosition(pos.x - 5.0f, pos.y - 5.0f);
            sf::Color color(120, 220, 180);
            if (i == selectedOriginIndex)
            {
                color = sf::Color::Green;
            }
            else if (i == selectedDestinationIndex)
            {
                color = sf::Color::Red;
            }
            else if (i == hoveredPortIndex)
            {
                color = sf::Color::Yellow;
            }
            circle.setFillColor(color);
            window.draw(circle);

            if (port.dockQueue.size() > 0)
            {
                int iconCount = minValue(4, port.dockQueue.size());
                for (int q = 0; q < iconCount; ++q)
                {
                    float offsetX = -18.0f + q * 12.0f;
                    float offsetY = -26.0f;
                    if (hasBoatTextures)
                    {
                        sf::Sprite queuedBoat(boatSouthTexture);
                        sf::Vector2u texSize = boatSouthTexture.getSize();
                        float targetSize = 20.0f;
                        float scale = targetSize / (float)texSize.x;
                        queuedBoat.setScale(scale, scale);
                        queuedBoat.setOrigin(texSize.x * 0.5f, texSize.y * 0.5f);
                        queuedBoat.setPosition(pos.x + offsetX, pos.y + offsetY);
                        window.draw(queuedBoat);
                    }
                    else
                    {
                        sf::CircleShape mini(3.0f);
                        mini.setFillColor(sf::Color::White);
                        mini.setPosition(pos.x + offsetX, pos.y + offsetY);
                        window.draw(mini);
                    }
                }
                char qbuf[32];
                std::snprintf(qbuf, sizeof(qbuf), "%d", port.dockQueue.size());
                sf::Text qText(qbuf, font, 12);
                qText.setFillColor(sf::Color::White);
                qText.setPosition(pos.x - 20.0f, pos.y - 34.0f);
                window.draw(qText);
            }

            char labelBuf[128];
            std::snprintf(labelBuf, sizeof(labelBuf), "%s  $%d", port.name, port.chargePerDay);
            sf::Text portLabel(labelBuf, font, 12);
            portLabel.setFillColor(sf::Color(210, 230, 255));
            portLabel.setOutlineColor(sf::Color(5, 5, 5, 180));
            portLabel.setOutlineThickness(1.0f);
            portLabel.setPosition(pos.x + 8.0f, pos.y - 6.0f);
            window.draw(portLabel);
        }

        // Draw animated boats
        for (int b = 0; b < gActiveBoats.size; ++b)
        {
            AnimatedBoat &boat = gActiveBoats[b];
            if (!boat.active)
                continue;

            sf::Vector2f screenPos = boat.position * zoomLevel + viewOffset;

            if (hasBoatTextures)
            {
                float angle = boat.currentAngle;
                while (angle < 0)
                    angle += 360.0f;
                while (angle >= 360.0f)
                    angle -= 360.0f;

                // Select texture based on direction
                sf::Texture *currentTexture = nullptr;
                if (angle >= 315.0f || angle < 45.0f)
                {
                    currentTexture = &boatEastTexture; // East: 179x166
                }
                else if (angle >= 45.0f && angle < 135.0f)
                {
                    currentTexture = &boatSouthTexture; // South: 162x240
                }
                else if (angle >= 135.0f && angle < 225.0f)
                {
                    currentTexture = &boatWestTexture; // West: 177x210
                }
                else
                {
                    currentTexture = &boatNorthTexture; // North: 172x207
                }

                sf::Sprite boatSprite(*currentTexture);
                sf::Vector2u texSize = currentTexture->getSize();
                float targetSize = 40.0f;
                float scale = targetSize / (float)texSize.x;
                boatSprite.setScale(scale, scale);
                boatSprite.setOrigin(texSize.x * 0.5f, texSize.y * 0.5f);
                boatSprite.setPosition(screenPos);
                window.draw(boatSprite);
            }
            else
            {
                sf::CircleShape boatCircle(8.0f);
                boatCircle.setOrigin(8.0f, 8.0f);
                boatCircle.setFillColor(sf::Color::Cyan);
                boatCircle.setPosition(screenPos);
                window.draw(boatCircle);
            }

            if (boat.state == BoatWaitingInQueue)
            {
                sf::CircleShape waitIndicator(12.0f);
                waitIndicator.setOrigin(12.0f, 12.0f);
                waitIndicator.setPosition(screenPos);
                waitIndicator.setFillColor(sf::Color(255, 255, 0, 80));
                waitIndicator.setOutlineColor(sf::Color::Yellow);
                waitIndicator.setOutlineThickness(2.0f);
                window.draw(waitIndicator);
            }
            else if (boat.state == BoatAtDock)
            {
                sf::CircleShape dockIndicator(12.0f);
                dockIndicator.setOrigin(12.0f, 12.0f);
                dockIndicator.setPosition(screenPos);
                dockIndicator.setFillColor(sf::Color(0, 255, 0, 80));
                dockIndicator.setOutlineColor(sf::Color::Green);
                dockIndicator.setOutlineThickness(2.0f);
                window.draw(dockIndicator);
            }
        }

        if (gNavPanelAnim > 0.01f)
        {
            sf::RectangleShape panelGlow(sf::Vector2f(panelWidth + ui.sx(30.0f), (float)currentHeight + ui.sy(40.0f)));
            panelGlow.setPosition(panelX - ui.sx(15.0f), -ui.sy(20.0f));
            panelGlow.setFillColor(gThemePalette.panelGlow);
            window.draw(panelGlow);

            sf::RectangleShape panelBackground(sf::Vector2f(panelWidth, (float)currentHeight));
            panelBackground.setPosition(panelX, 0.0f);
            panelBackground.setFillColor(gThemePalette.panelBackground);
            panelBackground.setOutlineColor(gThemePalette.panelOutline);
            panelBackground.setOutlineThickness(2.0f);
            window.draw(panelBackground);

            sf::RectangleShape panelAccent(sf::Vector2f(panelWidth, ui.sy(4.0f)));
            panelAccent.setPosition(panelX, 0.0f);
            panelAccent.setFillColor(gThemePalette.panelAccent);
            window.draw(panelAccent);

            float panelTextY = 20.0f;
            sf::Text header("OceanRoute Navigator", font, 28);
            header.setFillColor(gThemePalette.headerText);
            header.setLetterSpacing(1.08f);
            header.setPosition(panelLeft, panelTextY);
            window.draw(header);
            panelTextY += 50.0f;

            char statsBuf[128];
            std::snprintf(statsBuf, sizeof(statsBuf), "Ports: %d\nRoutes: %d", globalGraph.totalPorts, globalGraph.totalRoutes);
            sf::Text stats(statsBuf, font, 18);
            stats.setFillColor(gThemePalette.statsText);
            stats.setPosition(panelLeft, panelTextY);
            window.draw(stats);

            panelTextY += 60.0f;
            sf::RectangleShape dropdownBox(companyDropdownRect.getSize());
            dropdownBox.setPosition(companyDropdownRect.left, companyDropdownRect.top);
            dropdownBox.setFillColor(gThemePalette.dropdownFill);
            dropdownBox.setOutlineColor(gThemePalette.dropdownOutline);
            dropdownBox.setOutlineThickness(2.0f);
            window.draw(dropdownBox);
            int selectedCompanies = 0;
            std::string companyLabel;
            for (int i = 0; i < gCompanyOptions.size; ++i)
            {
                if (gCompanyOptions[i].selected)
                {
                    if (!companyLabel.empty())
                    {
                        companyLabel += ", ";
                    }
                    companyLabel += gCompanyOptions[i].name;
                    selectedCompanies++;
                }
            }
            if (companyLabel.empty())
                companyLabel = "Pick preferred companies";
            sf::Text companyText(companyLabel, font, 16);
            companyText.setFillColor(selectedCompanies > 0 ? gThemePalette.dropdownText : colorWithAlpha(gThemePalette.dropdownText, 150));
            companyText.setPosition(companyDropdownRect.left + ui.sx(10.0f), companyDropdownRect.top + ui.sy(8.0f));
            window.draw(companyText);
            if (showCompanyWarning)
            {
                sf::Text warn("* Required before planning", font, 14);
                warn.setFillColor(sf::Color(255, 120, 120));
                warn.setPosition(companyDropdownRect.left, companyDropdownRect.top - 22.0f);
                window.draw(warn);
            }

            auto drawDropdownBase = [&](const sf::FloatRect &rect, const std::string &value)
            {
                sf::RectangleShape box(rect.getSize());
                box.setPosition(rect.left, rect.top);
                box.setFillColor(gThemePalette.dropdownFill);
                box.setOutlineColor(gThemePalette.dropdownOutline);
                box.setOutlineThickness(2.0f);
                window.draw(box);
                sf::Text label(value, font, 16);
                label.setFillColor(gThemePalette.dropdownText);
                label.setPosition(rect.left + ui.sx(10.0f), rect.top + ui.sy(8.0f));
                window.draw(label);
            };

            auto drawDropdownEntries = [&](const sf::FloatRect &rect, DropdownState &state, const DynamicArray<std::string> &options)
            {
                float entryY = rect.top + rect.height;
                for (int i = 0; i < options.size; ++i)
                {
                    sf::FloatRect entry(rect.left, entryY + i * 32.0f, rect.width, 30.0f);
                    sf::RectangleShape entryShape(entry.getSize());
                    entryShape.setPosition(entry.left, entry.top);
                    bool isSelected = (i == state.selectedIndex);
                    bool isHighlighted = (i == state.highlightIndex);
                    sf::Color base = gThemePalette.dropdownEntry;
                    if (isSelected)
                        base = gThemePalette.dropdownEntrySelected;
                    if (isHighlighted)
                        base = gThemePalette.dropdownEntryHighlight;
                    entryShape.setFillColor(base);
                    entryShape.setOutlineColor(isHighlighted ? gThemePalette.dropdownEntryOutline : colorWithAlpha(gThemePalette.dropdownEntryOutline, 100));
                    entryShape.setOutlineThickness(1.5f);
                    window.draw(entryShape);
                    sf::Text entryLabel(options[i], font, 15);
                    entryLabel.setFillColor(gThemePalette.dropdownText);
                    entryLabel.setPosition(entry.left + ui.sx(8.0f), entry.top + ui.sy(4.0f));
                    window.draw(entryLabel);
                }
            };

            auto drawCompanyOverlay = [&]()
            {
                float entryY = companyDropdownRect.top + companyDropdownRect.height;
                for (int i = 0; i < gCompanyOptions.size; ++i)
                {
                    sf::FloatRect entryRect(companyDropdownRect.left, entryY + i * 34.0f, companyDropdownRect.width, 32.0f);
                    sf::RectangleShape entryShape(entryRect.getSize());
                    entryShape.setPosition(entryRect.left, entryRect.top);
                    sf::Color baseColor = gCompanyOptions[i].selected ? gThemePalette.dropdownEntrySelected : gThemePalette.dropdownEntry;
                    if (i == companyHighlightIndex)
                    {
                        baseColor = gThemePalette.dropdownEntryHighlight;
                    }
                    entryShape.setFillColor(baseColor);
                    entryShape.setOutlineColor(i == companyHighlightIndex ? gThemePalette.dropdownEntryOutline : colorWithAlpha(gThemePalette.dropdownEntryOutline, 100));
                    entryShape.setOutlineThickness(1.5f);
                    window.draw(entryShape);
                    sf::Text entryText(gCompanyOptions[i].name, font, 15);
                    entryText.setFillColor(gThemePalette.dropdownText);
                    entryText.setPosition(entryRect.left + ui.sx(8.0f), entryRect.top + ui.sy(4.0f));
                    window.draw(entryText);
                }
            };

            std::string dateValue = (dateDropdown.selectedIndex >= 0 && dateDropdown.selectedIndex < gAvailableDates.size) ? gAvailableDates[dateDropdown.selectedIndex] : std::string("Any");
            std::string timeValue = (timeDropdown.selectedIndex >= 0 && timeDropdown.selectedIndex < gAvailableTimes.size) ? gAvailableTimes[timeDropdown.selectedIndex] : std::string("Any");
            drawDropdownBase(dateDropdownRect, dateValue);
            drawDropdownBase(timeDropdownRect, timeValue);

            auto drawButton = [&](const UIButton &btn, bool active)
            {
                sf::Vector2f pos(btn.bounds.left, btn.bounds.top);
                sf::Vector2f size(btn.bounds.width, btn.bounds.height);

                sf::RectangleShape halo(size + sf::Vector2f(ui.sx(16.0f), ui.sy(12.0f)));
                halo.setPosition(pos.x - ui.sx(8.0f), pos.y - ui.sy(6.0f));
                sf::Color haloColor = gThemePalette.buttonHalo;
                haloColor.a = (sf::Uint8)(active ? haloColor.a : maxValue(20, haloColor.a / 2));
                halo.setFillColor(haloColor);
                window.draw(halo);

                sf::RectangleShape rect(size);
                rect.setPosition(pos);
                sf::Color base = active ? gThemePalette.buttonActiveFill : gThemePalette.buttonFill;
                if (btn.hovered)
                {
                    base.r = minValue(255, base.r + 25);
                    base.g = minValue(255, base.g + 25);
                    base.b = minValue(255, base.b + 25);
                }
                rect.setFillColor(base);
                rect.setOutlineColor(gThemePalette.buttonOutline);
                rect.setOutlineThickness(2.0f);
                window.draw(rect);

                sf::RectangleShape accent(sf::Vector2f(size.x, ui.sy(3.0f)));
                accent.setPosition(pos.x, pos.y);
                sf::Color accentColor = gThemePalette.buttonAccent;
                if (!active)
                    accentColor.a = maxValue(80, accentColor.a - 30);
                accent.setFillColor(accentColor);
                window.draw(accent);

                sf::Text text(btn.text, font, 18);
                text.setFillColor(gThemePalette.buttonText);
                text.setPosition(pos.x + ui.sx(14.0f), pos.y + ui.sy(12.0f));
                window.draw(text);
            };

            drawButton(buttons[ButtonFindCheapest], false);
            drawButton(buttons[ButtonFindFastest], false);
            drawButton(buttons[ButtonClear], false);
            drawButton(buttons[ButtonShowRoutes], showRouteOverlay);
            drawButton(buttons[ButtonToggleDirect], displayFilter == DisplayDirectOnly);
            drawButton(buttons[ButtonToggleConnections], displayFilter == DisplayConnectingOnly);
            if (removeButtonVisible)
            {
                bool activeRemoval = awaitingNodeRemoval && removalPlanIndex == highlightedRouteIndex;
                drawButton(removeButton, activeRemoval);
                if (activeRemoval)
                {
                    sf::Text removalHint("Select an intermediate port on the map.", font, 14);
                    removalHint.setFillColor(sf::Color(0, 255, 210));
                    removalHint.setPosition(removeButton.bounds.left, removeButton.bounds.top + removeButton.bounds.height + ui.sy(10.0f));
                    window.draw(removalHint);
                }
            }

            if (companyDropdownExpanded)
            {
                drawCompanyOverlay();
            }
            if (dateDropdown.expanded)
            {
                drawDropdownEntries(dateDropdownRect, dateDropdown, gAvailableDates);
            }
            if (timeDropdown.expanded)
            {
                drawDropdownEntries(timeDropdownRect, timeDropdown, gAvailableTimes);
            }
        }

        // Details toggle button (top-left)
        auto drawTopControlButton = [&](const sf::FloatRect &rect, const std::string &label, bool active)
        {
            sf::RectangleShape btn(rect.getSize());
            btn.setPosition(rect.left, rect.top);
            sf::Color base = gThemePalette.detailsFill;
            if (!active)
            {
                base.a = (sf::Uint8)(base.a * 0.9f);
            }
            btn.setFillColor(base);
            sf::Color outline = gThemePalette.detailsOutline;
            btn.setOutlineColor(outline);
            btn.setOutlineThickness(2.0f);
            window.draw(btn);

            sf::RectangleShape accent(sf::Vector2f(rect.width, ui.sy(3.0f)));
            accent.setPosition(rect.left, rect.top);
            accent.setFillColor(active ? gThemePalette.detailsAccent : colorWithAlpha(gThemePalette.detailsAccent, 160));
            window.draw(accent);

            sf::Text txt(label, font, 16);
            txt.setFillColor(gThemePalette.detailsText);
            txt.setPosition(rect.left + ui.sx(10.0f), rect.top + ui.sy(6.0f));
            window.draw(txt);
        };

        drawTopControlButton(detailsBtnRect, "Details", sidePanelOpen);
        drawTopControlButton(navClampBtnRect, gNavPanelOpen ? "Clamp Controls" : "Show Controls", gNavPanelOpen);
        drawTopControlButton(backToMenuRect, "Back to Menu", false);

        if (sidePanelAnim > 0.01f)
        {
            float panelAlpha = clampValue(sidePanelAnim, 0.0f, 1.0f);
            sf::RectangleShape sidePanel(sf::Vector2f(sidePanelWidth, (float)currentHeight));
            sidePanel.setPosition(sidePanelX, 0.0f);
            sf::Color sideFill = gThemePalette.sidePanelBackground;
            sideFill.a = (sf::Uint8)(sideFill.a * panelAlpha);
            sidePanel.setFillColor(sideFill);
            sf::Color sideOutline = gThemePalette.sidePanelOutline;
            sideOutline.a = (sf::Uint8)(sideOutline.a * panelAlpha);
            sidePanel.setOutlineColor(sideOutline);
            sidePanel.setOutlineThickness(1.0f);
            window.draw(sidePanel);

            sf::Text closeTxt("X", font, 16);
            sf::RectangleShape closeBox(sideCloseRect.getSize());
            closeBox.setPosition(sideCloseRect.left, sideCloseRect.top);
            closeBox.setFillColor(sf::Color(70, 40, 40));
            closeBox.setOutlineColor(sf::Color::White);
            closeBox.setOutlineThickness(1.0f);
            window.draw(closeBox);
            closeTxt.setFillColor(sf::Color::White);
            closeTxt.setPosition(sideCloseRect.left + ui.sx(7.0f), sideCloseRect.top + ui.sy(2.0f));
            window.draw(closeTxt);

            float headerY = sidePanelTop;
            sf::Text plannedHeader("Planned Routes", font, 20);
            plannedHeader.setFillColor(gThemePalette.sidePanelHeading);
            plannedHeader.setPosition(sidePanelX + sidePanelPadding, headerY);
            window.draw(plannedHeader);

            if (gRouteItemRects.size == 0)
            {
                sf::Text emptyMsg("No pending routes. Plan a route to start.", font, 14);
                emptyMsg.setFillColor(gThemePalette.sidePanelText);
                emptyMsg.setPosition(sidePanelX + sidePanelPadding, plannedListStartY + ui.sy(4.0f));
                window.draw(emptyMsg);
            }

            for (int idx = 0; idx < gRouteItemRects.size; ++idx)
            {
                int planIndex = gRouteItemPlanOrder[idx];
                if (planIndex < 0 || planIndex >= gPlannedRoutes.size)
                    continue;
                RoutePlan &plan = gPlannedRoutes[planIndex];
                const sf::FloatRect &rowRect = gRouteItemRects[idx];
                sf::RectangleShape row(rowRect.getSize());
                row.setPosition(rowRect.left, rowRect.top);
                row.setFillColor(planIndex == highlightedRouteIndex ? gThemePalette.plannedRowHighlight : gThemePalette.plannedRow);
                row.setOutlineColor(gThemePalette.plannedRowOutline);
                row.setOutlineThickness(1.0f);
                window.draw(row);

                sf::Text summary(plan.summary, font, 14);
                summary.setFillColor(gThemePalette.sidePanelText);
                summary.setPosition(rowRect.left + ui.sx(10.0f), rowRect.top + ui.sy(6.0f));
                window.draw(summary);

                char detailBuf[160];
                std::snprintf(detailBuf, sizeof(detailBuf), "Legs %d | %s %s", plan.simulatedLegs.size, plan.requestedDate, plan.requestedTime);
                sf::Text detail(detailBuf, font, 12);
                detail.setFillColor(colorWithAlpha(gThemePalette.sidePanelText, 200));
                detail.setPosition(rowRect.left + ui.sx(10.0f), rowRect.top + ui.sy(24.0f));
                window.draw(detail);

                const char *planState = plan.hasLaunched ? (plan.isCompleted ? "Completed" : "Launched") : "Ready";
                sf::Text stateText(planState, font, 12);
                stateText.setFillColor(plan.hasLaunched ? colorWithAlpha(gThemePalette.sidePanelHeading, 200) : gThemePalette.messageText);
                stateText.setPosition(rowRect.left + ui.sx(10.0f), rowRect.top + ui.sy(42.0f));
                window.draw(stateText);

                if (!plan.hasLaunched)
                {
                    sf::FloatRect startBtnRect(rowRect.left + rowRect.width - startButtonWidth - ui.sx(8.0f),
                                               rowRect.top + ui.sy(8.0f),
                                               startButtonWidth,
                                               rowRect.height - ui.sy(16.0f));
                    sf::RectangleShape startBtn(startBtnRect.getSize());
                    startBtn.setPosition(startBtnRect.left, startBtnRect.top);
                    startBtn.setFillColor(gThemePalette.startButtonFill);
                    startBtn.setOutlineColor(gThemePalette.buttonOutline);
                    startBtn.setOutlineThickness(1.0f);
                    window.draw(startBtn);
                    sf::Text startTxt("Start", font, 14);
                    startTxt.setFillColor(gThemePalette.startButtonText);
                    sf::FloatRect txtBounds = startTxt.getLocalBounds();
                    startTxt.setPosition(startBtnRect.left + (startBtnRect.width - txtBounds.width) * 0.5f,
                                         startBtnRect.top + (startBtnRect.height - txtBounds.height) * 0.5f - ui.sy(4.0f));
                    window.draw(startTxt);
                }
                else if (plan.isCompleted)
                {
                    sf::Text done("Done", font, 13);
                    done.setFillColor(sf::Color(180, 255, 180));
                    done.setPosition(rowRect.left + rowRect.width - ui.sx(64.0f), rowRect.top + ui.sy(22.0f));
                    window.draw(done);
                }
            }

            sf::Text runningHeader("Running Routes", font, 20);
            runningHeader.setFillColor(gThemePalette.sidePanelHeading);
            runningHeader.setPosition(sidePanelX + sidePanelPadding, runningSectionTop);
            window.draw(runningHeader);

            const float runningRowHeight = ui.sy(96.0f);
            const float runningRowSpacing = runningRowHeight + ui.sy(16.0f);
            float runningCursor = runningSectionTop + ui.sy(34.0f);
            bool hasRunning = false;
            float runningListEndY = runningCursor;
            for (int i = 0; i < gPlannedRoutes.size; ++i)
            {
                RoutePlan &plan = gPlannedRoutes[i];
                if (!plan.isRunning)
                    continue;
                hasRunning = true;
                sf::FloatRect runRect(sidePanelX + sidePanelPadding, runningCursor, sidePanelWidth - sidePanelPadding * 2.0f, runningRowHeight);
                sf::RectangleShape card(runRect.getSize());
                card.setPosition(runRect.left, runRect.top);
                card.setFillColor(gThemePalette.runningCard);
                card.setOutlineColor(gThemePalette.runningCardOutline);
                card.setOutlineThickness(1.0f);
                window.draw(card);

                const char *originName = "Origin";
                const char *destName = "Destination";
                if (plan.simulatedLegs.size > 0)
                {
                    LegSimulation &firstLeg = plan.simulatedLegs[0];
                    LegSimulation &lastLeg = plan.simulatedLegs[plan.simulatedLegs.size - 1];
                    if (firstLeg.edge)
                        originName = globalGraph.ports[firstLeg.edge->originIndex].name;
                    if (lastLeg.edge)
                        destName = globalGraph.ports[lastLeg.edge->destIndex].name;
                }
                char routeTitle[160];
                std::snprintf(routeTitle, sizeof(routeTitle), "%s -> %s", originName, destName);
                sf::Text routeText(routeTitle, font, 16);
                routeText.setFillColor(gThemePalette.sidePanelText);
                routeText.setPosition(runRect.left + ui.sx(10.0f), runRect.top + ui.sy(6.0f));
                window.draw(routeText);

                char infoBuf[160];
                std::snprintf(infoBuf, sizeof(infoBuf), "Cost $%.0f | %.1fh | %d legs | %s",
                              plan.realisticCost,
                              plan.realisticTime,
                              plan.simulatedLegs.size,
                              plan.mode == SearchCheapest ? "Cheapest" : "Fastest");
                sf::Text infoText(infoBuf, font, 13);
                infoText.setFillColor(colorWithAlpha(gThemePalette.sidePanelText, 210));
                infoText.setPosition(runRect.left + ui.sx(10.0f), runRect.top + ui.sy(30.0f));
                window.draw(infoText);

                AnimatedBoat *boatPtr = findActiveBoatForPlan(i);
                const char *statusStr = boatPtr ? boatStateToString(boatPtr->state) : "Syncing";
                if (!boatPtr && plan.runningProgress >= 1.0f)
                    statusStr = "Wrapping up";
                sf::Text statusText(statusStr, font, 13);
                statusText.setFillColor(gThemePalette.messageText);
                statusText.setPosition(runRect.left + ui.sx(10.0f), runRect.top + ui.sy(50.0f));
                window.draw(statusText);

                float progress = plan.runningProgress;
                progress = minValue(1.0f, maxValue(0.0f, progress));
                sf::RectangleShape progressBg(sf::Vector2f(runRect.width - ui.sx(20.0f), ui.sy(8.0f)));
                progressBg.setPosition(runRect.left + ui.sx(10.0f), runRect.top + runRect.height - ui.sy(22.0f));
                progressBg.setFillColor(gThemePalette.progressBg);
                window.draw(progressBg);
                sf::RectangleShape progressFill(sf::Vector2f(progressBg.getSize().x * progress, progressBg.getSize().y));
                progressFill.setPosition(progressBg.getPosition());
                progressFill.setFillColor(gThemePalette.progressFill);
                window.draw(progressFill);
                char pctBuf[32];
                std::snprintf(pctBuf, sizeof(pctBuf), "%d%%", (int)std::round(progress * 100.0f));
                sf::Text pctText(pctBuf, font, 12);
                pctText.setFillColor(gThemePalette.completedText);
                pctText.setPosition(progressBg.getPosition().x, progressBg.getPosition().y - ui.sy(16.0f));
                window.draw(pctText);

                runningCursor += runningRowSpacing;
            }
            if (hasRunning)
            {
                runningListEndY = runningCursor;
            }

            float completedTop = hasRunning ? runningListEndY + ui.sy(28.0f) : runningSectionTop + ui.sy(34.0f);
            sf::Text completedHeader("Completed Routes", font, 20);
            completedHeader.setFillColor(gThemePalette.sidePanelHeading);
            completedHeader.setPosition(sidePanelX + sidePanelPadding, completedTop);
            window.draw(completedHeader);

            float completedY = completedTop + ui.sy(32.0f);
            bool hasCompleted = false;
            for (int i = 0; i < gPlannedRoutes.size; ++i)
            {
                RoutePlan &plan = gPlannedRoutes[i];
                if (!plan.isCompleted)
                    continue;
                hasCompleted = true;
                sf::FloatRect cRect(sidePanelX + sidePanelPadding, completedY, sidePanelWidth - sidePanelPadding * 2.0f, ui.sy(54.0f));
                sf::RectangleShape cRow(cRect.getSize());
                cRow.setPosition(cRect.left, cRect.top);
                cRow.setFillColor(gThemePalette.completedRow);
                cRow.setOutlineColor(gThemePalette.sidePanelOutline);
                cRow.setOutlineThickness(1.0f);
                window.draw(cRow);

                sf::Text cSummary(plan.summary, font, 13);
                cSummary.setFillColor(gThemePalette.completedText);
                cSummary.setPosition(cRect.left + ui.sx(8.0f), cRect.top + ui.sy(6.0f));
                window.draw(cSummary);
                char cBuf[120];
                std::snprintf(cBuf, sizeof(cBuf), "$%.0f | %.1fh", plan.realisticCost, plan.realisticTime);
                sf::Text cInfo(cBuf, font, 12);
                cInfo.setFillColor(colorWithAlpha(gThemePalette.completedText, 200));
                cInfo.setPosition(cRect.left + ui.sx(8.0f), cRect.top + ui.sy(26.0f));
                window.draw(cInfo);
                completedY += ui.sy(62.0f);
            }
            if (!hasCompleted)
            {
                sf::Text none("No completed routes yet.", font, 14);
                none.setFillColor(gThemePalette.sidePanelText);
                none.setPosition(sidePanelX + sidePanelPadding, completedY);
                window.draw(none);
            }

            if (!actionMessage.empty() && actionMessageTimer > 0.0f)
            {
                sf::Text status(actionMessage, font, 14);
                status.setFillColor(gThemePalette.messageText);
                status.setPosition(sidePanelX + sidePanelPadding, completedY + ui.sy(18.0f));
                window.draw(status);
            }
        }

        if (showTooltip)
        {
            sf::RectangleShape tooltipBox(sf::Vector2f(220.0f, 70.0f));
            tooltipBox.setPosition(tooltipPosition.x + 10.0f, tooltipPosition.y + 10.0f);
            tooltipBox.setFillColor(sf::Color(10, 10, 10, 220));
            tooltipBox.setOutlineColor(sf::Color::White);
            tooltipBox.setOutlineThickness(1.0f);
            window.draw(tooltipBox);
            sf::Text tipText(tooltipText, font, 14);
            tipText.setPosition(tooltipBox.getPosition().x + 8.0f, tooltipBox.getPosition().y + 6.0f);
            window.draw(tipText);
        }
        if (showEdgeTooltip)
        {
            sf::RectangleShape tooltipBox(sf::Vector2f(260.0f, 90.0f));
            tooltipBox.setPosition(edgeTooltipPosition.x + 10.0f, edgeTooltipPosition.y + 10.0f);
            tooltipBox.setFillColor(sf::Color(10, 10, 10, 220));
            tooltipBox.setOutlineColor(sf::Color(255, 255, 255, 180));
            tooltipBox.setOutlineThickness(1.0f);
            window.draw(tooltipBox);
            sf::Text tipText(edgeTooltipText, font, 14);
            tipText.setPosition(tooltipBox.getPosition().x + 8.0f, tooltipBox.getPosition().y + 6.0f);
            window.draw(tipText);
        }

        window.display();
    }

    return 0;
}
