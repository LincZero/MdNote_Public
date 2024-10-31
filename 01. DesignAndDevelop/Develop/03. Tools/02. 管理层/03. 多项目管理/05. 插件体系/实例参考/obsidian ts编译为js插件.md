这里参考的是Obsidian的做法

## obsidian依赖

- node_modules/
  - obsidian/
    - .github/
      - ISSUE_TEMPLATE/
        - api-bug-report.md
    - obsidian.d.ts
    - package.json
    - README.md

### package.json

```json
{
    "name": "obsidian",
    "version": "0.16.3",
    "description": "Type definitions for the latest Obsidian API (https://obsidian.md)",
    "keywords": ["obsdmd"],
    "homepage": "https://obsidian.md",
    "repository": {
        "type": "git",
        "url": "https://github.com/obsidianmd/obsidian-api.git"
    },
    "license": "MIT",
    "main": "",
    "types": "obsidian.d.ts",
    "dependencies": {
        "@types/codemirror": "0.0.108",
        "moment": "2.29.4"
    },
    "peerDependencies": {
        "@codemirror/state": "^6.0.0",
        "@codemirror/view": "^6.0.0"
    }
}
```

### README.md (机翻+润色)

~~~makefile
## 黑曜石API

最新的 [Obsidian](https://obsidian.md) API的类型定义。

**警告:**黑曜石API仍处于早期alpha，随时可能发生变化!

### 文档

所有API文档都位于 `obsidian.d.ts` 文件中。

这将包括类型、属性、方法和解释每件事的注释。

有关如何创建Obsidian插件的完整示例，请使用 https://github.com/obsidianmd/obsidian-sample-plugin 上的模板

### 插件结构

`manifest.json`

- `id` 插件的id。
- `name` 插件的显示名称。
- `author` 插件作者的名字。
- `version` 插件的版本。
- `minAppVersion` 是插件所需的最低黑曜石版本。
- `description` 插件的长描述。
- `authorUrl` (可选)一个URL到你自己的网站。
- `isDesktopOnly` 无论你的插件使用NodeJS或Electron api。

`main.js`

- 这是插件的主要入口点
- 使用 `require('obsidian')` 导入任何Obsidian API
- 使用 `require('fs')` 或 `require('electron')` 导入 NodeJS 或 Electron API
- 必须导出一个继承了 `Plugin` 的默认类
- 必须使用 Rollup, Webpack，或其他javascript捆绑器 将所有外部依赖捆绑到这个文件中

### 应用架构

##### 该应用程序被组织成几个主要模块:

- `App`，拥有其他所有东西的全局对象。你可以在你的插件内通过 `this.app` 访问它。`App` 接口为以下接口提供了访问器
- `Vault`，该界面可让您与Vault中的文件和文件夹进行交互。
- `Workspace`，让您与屏幕上的窗格进行交互的界面。
- `MetadataCache`，包含关于每个markdown文件的缓存元数据的接口，包括标题，链接，嵌入，标签和块。

##### 此外，通过继承 `Plugin`，您可以:

- 使用 `this.addRibbonIcon` 添加丝带图标。
- 使用 `this.addStatusBarItem` 添加状态栏(底部)元素。
- 使用 `this.addCommand` 添加一个全局命令，可选地使用默认热键。
- 使用 `this.addSettingTab` 添加插件设置选项卡。
- 使用 `this.registerView` 注册一种新的视图。
- 使用 `this.loadData` 和 `this.saveData` 保存和加载插件数据。

##### 注册事件

要从任何事件接口注册事件，如 `App` 和 `Workspace`，请使用 `this.registerEvent`，它会在插件卸载时自动卸载你的事件处理程序:

```typescript
this.registerEvent(app.on('event-name', callback));
```

如果你在插件卸载后为页面上的元素注册DOM事件，比如' window '或' document '事件，请使用' this.registerDomEvent ':

```typescript
this.registerDomEvent(element, 'click', callback);
```

如果你使用 `setInterval`，请使用 `this.registerInterval`:

```typescript
this.registerInterval(setInterval(callback, 1000));
```
~~~

### obsidian.d.ts

一共有4394行，md软件抗不住，就不放上来了。

如果后续需要分析，会分N个文件进行解析

不过大纲还是比较清晰的

```typescript
// 此处省略全局函数
declare global {
	interface ObjectConstructor;
    interface Array<T>;
	interface Math;
    interface StringConstructor;
    interface String;
    interface NumberConstructor;
    interface Node;
    interface Element extends Node;
    interface HTMLElement extends Element;
    interface Element extends Node;
    interface HTMLElement extends Element;
    interface DocumentFragment extends Node, NonElementParentNode, ParentNode;
    interface DomElementInfo;
    interface Node;
    interface EventListenerInfo;
    interface HTMLElement extends Element;
    interface Document;
    interface UIEvent extends Event;
    interface AjaxOptions;
    interface Window extends EventTarget, AnimationFrameProvider, GlobalEventHandlers, WindowEventHandlers, WindowLocalStorage, WindowOrWorkerGlobalScope, WindowSessionStorage;
    interface Touch;
}
export class AbstractTextComponent<T extends HTMLInputElement | HTMLTextAreaElement> extends ValueComponent<string>;
export class App;
export abstract class BaseComponent;
export interface BlockCache extends CacheItem;
export interface BlockSubpathResult extends SubpathResult;
export class ButtonComponent extends BaseComponent;
export interface CachedMetadata;
export interface CacheItem;
export interface CloseableComponent;
export class ColorComponent extends ValueComponent<string>;
export interface Command;
export class Component;
export type Constructor<T> = abstract new (...args: any[]) => T;
export interface DataAdapter;
export interface DataWriteOptions;
export function debounce<T extends unknown[], V>(cb: (...args: [...T]) => V, timeout?: number, resetTimer?: boolean): Debouncer<T, V>;
export interface Debouncer<T extends unknown[], V>;
export class DropdownComponent extends ValueComponent<string>;
export abstract class EditableFileView extends FileView;
export abstract class Editor;
export interface EditorChange extends EditorRangeOrCaret;
export interface EditorPosition;
export interface EditorRange;
export interface EditorRangeOrCaret;
export interface EditorScrollInfo;
export interface EditorSelection;
export interface EditorSelectionOrCaret;
export abstract class EditorSuggest<T> extends PopoverSuggest<T>;
export interface EditorSuggestContext extends EditorSuggestTriggerInfo;
export interface EditorSuggestTriggerInfo;
export interface EditorTransaction;
export interface EmbedCache extends ReferenceCache;
export interface EventRef;
export class Events;
export class ExtraButtonComponent extends BaseComponent;
export class FileManager;
export interface FileStats;
export class FileSystemAdapter implements DataAdapter;
export abstract class FileView extends ItemView;
export interface FrontMatterCache extends CacheItem;
export interface FuzzyMatch<T>;
export abstract class FuzzySuggestModal<T> extends SuggestModal<FuzzyMatch<T>>;
…… // 不行，太多了，刚开始没想到有这么多
```

## 具体分析

略























