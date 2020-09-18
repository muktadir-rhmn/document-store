//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_DATABASE_MANAGER_IMP_H
#define DOCUMENT_STORE_DATABASE_MANAGER_IMP_H

#include <map>
#include "../../api/database_manager.h"
#include "lib/wiredtiger.h"

namespace storageengine { namespace wiredtiger{

class DatabaseManagerImp : public DatabaseManager {
public:
    DatabaseManagerImp();

    ~DatabaseManagerImp();

    void createDatabase(String databaseName) override;

    Database *getDatabase(String databaseName) override;

    void releaseDatabase(Database* database) override;

private:
    const String DURABILITY_CONFIGURATION = "log=(enabled),transaction_sync=(enabled=true,method=none),"; ///Ref: https://source.wiredtiger.com/develop/tune_durability.html
    const String COMPRESSOR_CONFIGURATION = "extensions=[./libwiredtiger_zlib.so],"; ///ref: https://source.wiredtiger.com/develop/compression.html

    WT_CONNECTION* connection;
    Map<String, WT_CONNECTION* > connectionMap_;

    static String GetDatabaseDirectory(String &databaseName);
};

}}

#endif //DOCUMENT_STORE_DATABASE_MANAGER_IMP_H
