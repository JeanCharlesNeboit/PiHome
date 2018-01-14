## Install
```bash
npm install
```

- add `db_config.json` file in `./database`
  ```json
  {
    "host" : "IP",
    "user" : "USERNAME",
    "password" : "PASSWORD",
    "database" : "DATABASE"
  }
  ```
- add `config.json` file
  ```json
  {
    "secretKey": "SECRETKEY",
    "allowIPs": ["IP"]
  }
  ```

## Start
```bash
npm start
```
