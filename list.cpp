void listAll(string path, const File* f)  // two-parameter overload
{
    if (f->files() == nullptr)
    {
        path += f->name();
        cout << path << endl;
    }

    else if (f->files()->size() == 0)
    {
        path += f->name() + "/";
        cout << path << endl;
    }

    else if (f->name() != "" && path != f->name())
    {
        path += f->name() + "/";
        cout << path << endl;
    }

    else if (f->name() != "" && path == f->name())
    {
        path += "/";
        cout << path << endl;
    }
 


    if (f->files() == nullptr || f->files()->size() == 0)
    {
        if (path[path.length() - 1] != '/')
        {
            path = path.substr(0, path.length() - 2);
            return;
        }
        return;
    } 

    for (File* filePointer : *(f->files()))
    {
        if (path[path.length() - 1] != '/')
            path += "/";
        listAll(path, filePointer);
    }
}
