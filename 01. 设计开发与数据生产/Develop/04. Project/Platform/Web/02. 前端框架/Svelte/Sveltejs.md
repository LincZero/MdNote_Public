# Svelte

# 目录

# Svelte

https://www.sveltejs.cn/（有中文，挺好）

Table.svelte

这个官网文档就**非常非常非常不错**，而且网站上还有配套的在线运行

## 简介

#### 使用

```tsx
<script>
	let name = 'world';
</script>

<h1>Hello {name.toUpperCase()}!</h1>
```

#### 语法糖

```tsx
<script>
	let src = 'tutorial/image.gif';
	let name = 'Rick Astley';
</script>

<img src={src} alt="{name} dances.">	普通写法
<img {src} alt="{name} dances.">		语法糖
    
    
```

#### 样式

```tsx
<style>
	p {
		color: purple;
		font-family: 'Comic Sans MS', cursive;
		font-size: 2em;
	}
</style>

<p>This is a paragraph.</p>
```

#### 导入

```tsx
// App.svelte
<script>
	import Nested from './Nested.svelte';
</script>

<p>This is a paragraph.</p>
<Nested/>
    
// Nested.scelte
<p>This is another paragraph.</p>
```

#### html方式渲染

```tsx
<script>
	let string = `this string contains some <strong>HTML!!!</strong>`;
</script>

<p>{@html string}</p>
// @attention 如果使用此功能，则必须手动转义来自不信任源的 HTML 代码，否则会使用户面临 XSS 攻击的风险
```

官方提供了针对 [Rollup](https://rollupjs.org/) 和 [webpack](https://webpack.js.org/) 的插件，另外还有很多是[社区维护的插件](https://github.com/sveltejs/integrations#bundler-plugins)。



## 反应性能力

#### 普通赋值语句

```tsx
<script>
	let count = 0;

	function handleClick() {
		count += 1;
	}
</script>

<button on:click={handleClick}>
	Clicked {count} {count === 1 ? 'time' : 'times'}
</button>
```

#### 反应式声明（reactive declarations）

```tsx
<script>
	let count = 0;
	$: doubled = count * 2;		// 更新dom时，自动计算

	function handleClick() {
		count += 1;
	}
</script>

<button on:click={handleClick}>
	Clicked {count} {count === 1 ? 'time' : 'times'}
</button>

<p>{count} doubled is {doubled}</p>
```

#### 语句

```tsx
<script>
	let count = 0;

	$: if (count >= 10) {
		alert(`count is dangerously high!`);
		count = 9;
	}

	function handleClick() {
		count += 1;
	}

	// 你可以轻松地将一组语句组合成一个代码块
    $: {
        console.log(`the count is ${count}`);
        alert(`I SAID THE COUNT IS ${count}`);
    }
</script>

<button on:click={handleClick}>
	Clicked {count} {count === 1 ? 'time' : 'times'}
</button>
```

#### 更新数组和对象

```tsx
// 由于 Svelte 的反应性是由赋值语句触发的，因此使用数组的诸如 push 和 splice 之类的方法就不会触发自动更新。例如，点击按钮就不会执行任何操作
// 解决该问题的一种方法是添加一个多余的赋值语句：
function addNumber() {
	numbers.push(numbers.length + 1);
	numbers = numbers;
}
// 但还有一个更惯用的解决方案：
function addNumber() {
	numbers = [...numbers, numbers.length + 1];
}
// 你可以使用类似的模式来替换 pop、shift、unshift 和 splice 方法。
numbers[numbers.length] = numbers.length + 1;	// 我怎么感觉这方法很危险呢……
```

## 属性

#### 声明属性

```tsx
// Nested.svelte
<script>
	export let answer;	// 声明属性
</script>

<p>The answer is {answer}</p>

// App.svelte
<script>
	import Nested from './Nested.svelte';
</script>

<Nested answer={42}/>
```

#### 默认值

```tsx
<script>
	export let answer = 'a mystery';
</script>
```

#### 属性传递

```tsx
// Info.svelte
<script>
	export let name;
	export let version;
	export let speed;
	export let website;
</script>

<p>
	The <code>{name}</code> package is {speed} fast.
	Download version {version} from <a href="https://www.npmjs.com/package/{name}">npm</a>
	and <a href={website}>learn more here</a>
</p>

// App.svelte
<script>
	import Info from './Info.svelte';

	const pkg = {
		name: 'svelte',
		version: 3,
		speed: 'blazing',
		website: 'https://svelte.dev'
	};
</script>

<Info {...pkg}/>	// 传递多个参数过去
```

## 逻辑

原生HTML没有判断循环等逻辑

#### if语句

```tsx
<script>
	let user = { loggedIn: false };

	function toggle() {
		user.loggedIn = !user.loggedIn;	// 切换
	}
</script>

{#if user.loggedIn}
	<button on:click={toggle}>
		Log out
	</button>
{/if}

{#if !user.loggedIn}
	<button on:click={toggle}>
		Log in
	</button>
{/if}
```

#### else和else-if语句

```tsx
{#if x > 10}
	<p>{x} is greater than 10</p>
{:else if 5 > x}
	<p>{x} is less than 5</p>
{:else}
	<p>{x} is between 5 and 10</p>
{/if}
```

#### 循环 each块

```tsx
<script>
	let cats = [
		{ id: 'J---aiyznGQ', name: 'Keyboard Cat' },
		{ id: 'z_AbfPXTKms', name: 'Maru' },
		{ id: 'OUtn3pvWmpg', name: 'Henri The Existential Cat' }
	];
</script>

<h1>The Famous Cats of YouTube</h1>

<ul>
	{#each cats as { id, name }, i}
		<li><a target="_blank" href="https://www.youtube.com/watch?v={id}">
			{i + 1}: {name}
		</a></li>
	{/each}
</ul>
```

#### 为each块添加key值

```tsx
<script>
	import Thing from './Thing.svelte';

	let things = [
		{ id: 1, color: '#0d0887' },
		{ id: 2, color: '#6a00a8' },
		{ id: 3, color: '#b12a90' },
		{ id: 4, color: '#e16462' },
		{ id: 5, color: '#fca636' }
	];

	function handleClick() {
		things = things.slice(1);
	}
</script>

<button on:click={handleClick}>
	Remove first thing
</button>

{#each things as thing (thing.id)}
	<Thing current={thing.color}/>
{/each}
```

#### await块（promise）

```tsx
<script>
	let promise = getRandomNumber();	// 这是一个异步函数

	async function getRandomNumber() {
		const res = await fetch(`tutorial/random-number`);
		const text = await res.text();

		if (res.ok) {
			return text;
		} else {
			throw new Error(text);
		}
	}

	function handleClick() {
		promise = getRandomNumber();
	}
</script>

<button on:click={handleClick}>
	generate random number
</button>

{#await promise}
	<p>...waiting</p>
{:then number}
	<p>The number is {number}</p>
{:catch error}
	<p style="color: red">{error.message}</p>
{/await}
```

## 事件

#### DOM 事件

```tsx
<script>
	let m = { x: 0, y: 0 };

	function handleMousemove(event) {
		m.x = event.clientX;
		m.y = event.clientY;
	}
</script>

<style>
	div { width: 100%; height: 100%; }
</style>

<div on:mousemove={handleMousemove}>
	The mouse position is {m.x} x {m.y}
</div>
```

你也可以内联声明事件处理程序：

```tsx
<script>
	let m = { x: 0, y: 0 };
</script>

<style>
	div { width: 100%; height: 100%; }
</style>

<div on:mousemove="{e => m = { x: e.clientX, y: e.clientY }}">
	The mouse position is {m.x} x {m.y}
</div>
```

#### 事件修饰符

```tsx
<script>
	function handleClick() {
		alert('no more alerts')
	}
</script>

<button on:click|once={handleClick}>	// once：运行一次事件处理程序后将其删除。
	Click me
</button>
```

所有修饰符列表：

-   `preventDefault` ：调用`event.preventDefault()` ，在运行处理程序之前调用。比如，对客户端表单处理有用。
-   `stopPropagation` ：调用 `event.stopPropagation()`, 防止事件影响到下一个元素。
-   `passive` ： 优化了对 touch/wheel 事件的滚动表现(Svelte 会在合适的地方自动添加滚动条)。
-   `capture` — 在 *capture* 阶段而不是*bubbling* 阶段触发事件处理程序 ([MDN docs](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Building_blocks/Events#Event_bubbling_and_capture))
-   `once` ：运行一次事件处理程序后将其删除。
-   `self` — 仅当 event.target 是其本身时才执行。

你可以将修饰符组合在一起使用，例如：`on:click|once|capture={...}`。















