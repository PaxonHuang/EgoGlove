# Repository-Local Graphify Retirement Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Retire Graphify from EgoGlove repository-local operational instructions while retaining all generated graph outputs as historical artifacts and making CodeBaseMemory MCP the documented project intelligence workflow.

**Architecture:** The existing dedicated CBM project `home-EchoGloveHugeProjects-EgoGlove` is the active knowledge index. Only repository-local guidance changes: `CLAUDE.md` directs future queries to CBM and `docs/ARCHITECTURE_MEMORY.md` records the migration boundary. Graphify output trees remain untouched, global MCP configuration is unchanged, and no source/protocol/test/V7/history files are modified.

**Tech Stack:** CodeBaseMemory MCP v0.9.0; dedicated project `/home/EchoGloveHugeProjects/EgoGlove`; Markdown instructions and git.

## Global Constraints

- Do not alter firmware, protocol code, tests, `docs/V7/` architecture decisions, or git history.
- Do not uninstall Graphify, modify global settings/hooks, or edit `/root/.claude/.mcp.json`.
- Keep `graphify-out/`, `graphify-out/2026-08-04/`, and `relay/graphify-out/` in their existing paths as historical generated artifacts.
- Do not stage existing dirty files: `firmware/shared/test/test_hand_token` or `graphify-out/cache/last_query_stamp`.
- Commit only the selected repository-local instruction/documentation files.
- Continue to distinguish code/test evidence from design/roadmap statements.

---

### Task 1: Verify CBM knowledge quality and document results

**Files:**
- Modify: `docs/ARCHITECTURE_MEMORY.md`
- Read only: `CLAUDE.md`, `docs/V7/STRATEGY.md`, `docs/V7/ARCHITECTURE.md`, `relay/hand_token.py`, `relay/openxr_adapter.py` (BP 仅存于独立仓 `PaxonHuang/BP`)

**Interfaces:**
- Consumes CBM project `home-EchoGloveHugeProjects-EgoGlove`.
- Produces a concise query-quality record that names the right tool per knowledge type.

- [ ] **Step 1: Confirm dedicated index readiness.**

Run:

```bash
/root/.local/bin/codebase-memory-mcp cli index_status --project home-EchoGloveHugeProjects-EgoGlove
```

Expected: `status` is `ready`, root is `/home/EchoGloveHugeProjects/EgoGlove`, and results contain no parent-workspace source paths.

- [ ] **Step 2: Validate Hand Token v2 and canonical-20 with code-symbol tools.**

Use CBM `search_graph` and `get_architecture` to locate:

```text
relay/hand_token.py: serialize_v2, parse_v2, fk21
firmware/shared/hand_token.c: hand_token_v2_serialize, hand_token_v2_parse
relay/test_hand_token.py: golden and FK tests
relay/openxr_adapter.py: openxr_to_hand_token
```

Compare the result with `docs/V7/STRATEGY.md` D11/D12 and the v2 spec. Record that CBM answers implementation-relationship questions through graph symbols.

- [ ] **Step 3: Validate roadmap and ecosystem facts with documentation retrieval.**

Use CBM `search_code` with `file_pattern="*.md"`, `regex=true`, and path filters under `docs/V7`, `docs/BP`, plus `CLAUDE.md`. Query separately for:

```text
Lite|Pro
canonical-20|MediaPipe
MANO|OpenXR|FreeMoCap|ROS2
```

Do not rely on `search_graph` for prose roadmap answers: it ranks code symbols and may not surface Markdown sections. Record this operational distinction in the architecture memory document.

- [ ] **Step 4: Add a concise validation record.**

Add a `CBM Query Quality` subsection to `docs/ARCHITECTURE_MEMORY.md` with these four questions and required evidence sources:

```text
Hand Token v2 design -> search_graph/get_architecture plus v2 spec
canonical-20 topology -> search_code docs/V7 + v2 spec, then code FK evidence
adapter strategy -> search_graph relay adapter symbols + docs/BP mapping matrix
EgoMotion roadmap -> search_code docs/V7/docs/BP + CLAUDE.md, not code-symbol ranking alone
```

- [ ] **Step 5: Verify scope.**

```bash
git diff -- docs/ARCHITECTURE_MEMORY.md
git diff --check
```

Expected: only the architecture-memory document changes.

---

### Task 2: Replace repository-local Graphify instructions with CBM workflow

**Files:**
- Modify: `CLAUDE.md`
- Modify: `docs/ARCHITECTURE_MEMORY.md`
- Do not modify: Graphify output directories, global config, `docs/V7/`, source, tests, firmware.

**Interfaces:**
- Consumes verified CBM project and query-quality rules from Task 1.
- Produces the repository-local operational contract for future codebase questions.

- [ ] **Step 1: Replace the active Graphify discipline paragraph in `CLAUDE.md`.**

Replace the current Graphify query/update instruction with concise CBM guidance:

```markdown
当需要理解代码库结构、符号关系、调用链或变更影响时，优先使用 CodeBaseMemory MCP 项目 `home-EchoGloveHugeProjects-EgoGlove`：先 `get_architecture` / `search_graph` 缩小范围，需要调用关系时用 `trace_path`，读取已定位符号用 `get_code_snippet`。查询战略、路线图、互操作或其他文档事实时，用 `search_code` 限定 `*.md` 与 `docs/` 路径，并回链到 `docs/V7/STRATEGY.md`、`docs/V7/ARCHITECTURE.md` 或相关 spec。Graphify 输出仅保留为历史生成物，不再作为默认项目智能层；不得在常规代码/文档改动后运行 `graphify update .`。
```

Retain the rest of the work-discipline section unchanged.

- [ ] **Step 2: Update the Graphify coexistence section in architecture memory.**

Replace the wording that treats Graphify as active coexistence with:

```text
Graphify has been retired from repository-local operational workflow. Existing output directories remain historical artifacts in place. No global uninstall or global setting change occurred. Future deletion, archival relocation, hook cleanup, or uninstall remains a separately approved action.
```

- [ ] **Step 3: Validate the exact repository-local reference set.**

Run:

```bash
rg -n -i "graphify|codebase-memory|codebasememory|CBM" CLAUDE.md docs/ARCHITECTURE_MEMORY.md .gitignore
```

Expected: `CLAUDE.md` has CBM as the default workflow; historical retention is explicit; `.gitignore` is unchanged; Graphify output directories are not deleted or moved.

- [ ] **Step 4: Verify no generated artifact was staged.**

```bash
git diff --check
git status --short
git diff --name-only
```

Expected staged/unstaged migration paths are only `CLAUDE.md` and `docs/ARCHITECTURE_MEMORY.md`; existing dirty binary/cache paths remain unmodified and unstaged.

---

### Task 3: Commit and verify the repository-local retirement milestone

**Files:**
- Modify: `CLAUDE.md`
- Modify: `docs/ARCHITECTURE_MEMORY.md`

**Interfaces:**
- Consumes approved CBM workflow documentation.
- Produces one documentation-only migration commit.

- [ ] **Step 1: Perform final evidence checks.**

Run:

```bash
/root/.local/bin/codebase-memory-mcp cli index_status --project home-EchoGloveHugeProjects-EgoGlove
git config user.name
git config user.email
git diff --check
git diff -- CLAUDE.md docs/ARCHITECTURE_MEMORY.md
git status --short
```

Expected identity is `PaxonHuang <quenchkidney@outlook.com>`. Confirm CBM remains ready and no global configuration was changed.

- [ ] **Step 2: Commit only migration instructions.**

```bash
git add CLAUDE.md docs/ARCHITECTURE_MEMORY.md
git commit -m "docs: retire Graphify workflow for CBM"
```

Do not include `firmware/shared/test/test_hand_token`, `graphify-out/cache/last_query_stamp`, Graphify outputs, or any other paths.

- [ ] **Step 3: Verify commit contents.**

```bash
git show --stat --oneline HEAD
git show --name-only --format= HEAD
git status --short
```

Expected commit contains only the two documentation/instruction files. Existing Graphify outputs remain present and the two pre-existing dirty paths remain outside the commit.

- [ ] **Step 4: Report the retirement boundary.**

Report the CBM project name/root, the four-question validation method, commit hash, retained Graphify output locations, unchanged global configuration, and explicit future-only Graphify deletion/uninstall gate. Do not push unless separately instructed.
