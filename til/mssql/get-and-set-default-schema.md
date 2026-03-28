# Get and set the default schema in MSSQL

> [!warning]
> When running interactively through a database explorer or similar, make sure the right database is used. If you're in doubt, it doesn't hurt to `USE database;` for good measure.

## Get
```sql
USE database;
SELECT SCHEMA_NAME()
```

## Update
```sql
USE database;
ALTER USER username WITH DEFAULT_SCHEMA = schema;
```

Not sure what permissions this requires, but a `db_owner` seems to be able to modify itself.

## Exception
Note that this is with the exception of sysadmins:

> The value of DEFAULT_SCHEMA is ignored if the user is a member of the **sysadmin** fixed server role. All members of the **sysadmin** fixed server role have a default schema of `dbo`.
> https://learn.microsoft.com/en-us/sql/t-sql/statements/alter-user-transact-sql?view=sql-server-ver17&redirectedfrom=MSDN (2026-03-26)
