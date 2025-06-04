class EditString
{
public:
    EditString(void) : mInsert(true), mPosition(mText.begin()), mCaret(0)
    {}

    EditString( std::string newText )
    {
        setText( newText );
    }

    ~EditString(void)
    {}

protected:
    // The text for editing
    std::string mText;

    // Overwrite or insert
    bool mInsert;

    // Position for insert / overwrite
    std::string::iterator mPosition;

    // Caret Position - for positioning the cursor.
    int mCaret;

public:
    void setText( std::string & newText )
    {
        mText = newText;
        mPosition = mText.end();
        mCaret = (int)mText.length();
    }

    std::string & getText() {
        return mText;
    }

    void clear()
    {
        mText.clear();
        mPosition = mText.end();
        mCaret = 0;
    }

    bool inserting() {
        return mInsert;
    }

    bool injectKeyPress( const OIS::KeyEvent );

    // gets the current position in the text for cursor placement
    int getPosition(void) {
        return mCaret;
    }
};

bool EditString::injectKeyPress( const OIS::KeyEvent arg )
{
    bool keyUsed = true;

    if ( isgraph( arg.text ) || isspace( arg.text ) )
    {
        if ( mInsert || mPosition == mText.end() )
        {
            mPosition = mText.insert( mPosition, arg.text );
        }
        else
        {
            *mPosition = arg.text;
        }
        mPosition++;
        mCaret++;
    }
    else
    {
        switch ( arg.key )
        {
        case OIS::KC_BACK:
            if ( mPosition != mText.begin() )
            {
                mPosition = mText.erase( --mPosition );
                --mCaret;
            }
            break;

        case OIS::KC_INSERT:
            mInsert = ! mInsert;
            break;

        case OIS::KC_HOME:
            mPosition = mText.begin();
            mCaret = 0;
            break;

        case OIS::KC_END:
            mPosition = mText.end();
            mCaret = (int)mText.length();
            break;

        case OIS::KC_LEFT:
            if ( mPosition != mText.begin() )
            {
                mPosition--;
                mCaret--;
            }
            break;

        case OIS::KC_RIGHT:
            if ( mPosition != mText.end() )
            {
                mPosition++;
                mCaret++;
            }
            break;

        case OIS::KC_DELETE:
            if ( mPosition != mText.end() )
                mPosition = mText.erase( mPosition );
            break;

        default:
            keyUsed = false;
            break;
        }
    }

    return keyUsed;
}