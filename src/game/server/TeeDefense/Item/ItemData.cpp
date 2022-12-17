#include "ItemData.h"

// Init Item
CItem::CItem()
{
    // Init all options.(what?)
    str_copy(m_Name, "", sizeof(m_Name));
    m_Type = -1;
}