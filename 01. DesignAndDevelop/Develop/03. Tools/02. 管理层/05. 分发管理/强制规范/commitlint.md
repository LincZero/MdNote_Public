这个是 Node.js 的库，commitlint 和 husky 通常配合使用

```bash
npm install --save-dev @commitlint/{config-conventional,cli} husky
```

commitlint.config.js

```js
module.exports = {
  extends: ['@commitlint/config-conventional'],
};
```

package.json

```json
{
  "husky": {
    "hooks": {
      "commit-msg": "commitlint -E HUSKY_GIT_PARAMS"
    }
  }
}
```

