# Configuration Reduction Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Reduce default Claude Code context and configuration surface for EgoGlove while preserving the firmware, Python, ROS/data, Git, testing, and documentation workflow.

**Architecture:** Keep project strategy and architecture in the repository documents, and make `EgoGlove/CLAUDE.md` an indexed operating contract. Reduce global defaults through plugin enablement and reduce project-local permission noise without deleting installed caches. Collapse project memory to current, non-duplicative state pointers and validate every edited JSON/Markdown file before completion.

**Tech Stack:** Markdown, JSON, Claude Code settings, shell/Python validation, Git diff tooling.

## Global Constraints

- Do not modify business code, firmware, models, relay, SDK, web, or tests.
- Do not push, force-push, reset, checkout away user changes, or rewrite Git history.
- Preserve `PaxonHuang <quenchkidney@outlook.com>` as the required commit identity and prohibit AI co-author lines in repository guidance.
- Preserve the four truth levels: `已实现`, `工程可实现`, `需研发验证`, `长期方向`.
- Preserve the rule that major decisions or major discoveries stop for user confirmation.
- Keep `docs/V7/STRATEGY.md` and `docs/V7/ARCHITECTURE.md` as the strategic and architectural sources of truth.
- Do not delete plugin caches; settings changes must be reversible by restoring backups.
- Never print or copy credentials from Claude settings into documentation or final output.

---

### Task 1: Replace duplicated project instructions with an indexed contract

**Files:**
- Modify: `/home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md`
- Reference: `/home/EchoGloveHugeProjects/EgoGlove/docs/V7/STRATEGY.md`
- Reference: `/home/EchoGloveHugeProjects/EgoGlove/docs/V7/ARCHITECTURE.md`

**Interfaces:**
- Consumes: Existing V7 strategy, architecture, repository structure, branch policy, truth-level, Git, graphify, and historical migration rules.
- Produces: A 60–80 line project instruction file that points to the source documents instead of duplicating them.

- [ ] **Step 1: Write the compact Markdown contract**

Include these exact sections: project scope, source-of-truth documents, repository map, branch policy, truth levels, Git identity and commit rules, graphify workflow, decision escalation, technical reality guardrails, historical repository pointer, and memory pointer. Do not reproduce D1–D12 tables or architecture diagrams.

- [ ] **Step 2: Validate required constraints are present**

Run:
```bash
rg -n "PaxonHuang|quenchkidney@outlook.com|Co-Authored|已实现|工程可实现|需研发验证|长期方向|重大|STRATEGY.md|ARCHITECTURE.md|graphify" CLAUDE.md
wc -l CLAUDE.md
```
Expected: all required concepts are present and line count is between 60 and 80.

- [ ] **Step 3: Check the diff for accidental strategy loss**

Run:
```bash
git diff --check -- CLAUDE.md
git diff -- CLAUDE.md
```
Expected: no whitespace errors; only intentional compression and source-document pointers.

---

### Task 2: Reduce default plugin and tool loading

**Files:**
- Modify: `/root/.claude/settings.json`
- Backup: `/root/.claude/settings.json.bak-20260729`
- Reference: `/home/EchoGloveHugeProjects/.claude/settings.json`

**Interfaces:**
- Consumes: Existing enabled plugin map and project hook configuration.
- Produces: A smaller default plugin map retaining `superpowers`, `context7`, `remember`, `code-simplifier`, `clangd-lsp`, and `claude-md-management`; disables unrelated default plugins such as frontend design, Playwright, Cloudflare, Java LSP, Pyright LSP, skill creator, hookify, commit commands, and setup automation.

- [ ] **Step 1: Create a byte-for-byte backup**

Run:
```bash
cp -p /root/.claude/settings.json /root/.claude/settings.json.bak-20260729
```

- [ ] **Step 2: Replace only the enabled plugin map**

Preserve `env`, `attribution`, `model`, and `theme`. Set the enabled plugin map to the retained default set. Do not alter authentication or model environment values.

- [ ] **Step 3: Validate JSON and plugin count**

Run:
```bash
python3 -m json.tool /root/.claude/settings.json >/dev/null
python3 - <<'PY'
import json
p='/root/.claude/settings.json'
d=json.load(open(p))
print('\n'.join(f'{k}: {v}' for k,v in d['enabledPlugins'].items()))
print('enabled=', sum(d['enabledPlugins'].values()))
PY
```
Expected: valid JSON and 6 retained enabled plugins.

---

### Task 3: Replace accumulated project-local permissions with a minimal reversible allowlist

**Files:**
- Modify: `/home/EchoGloveHugeProjects/.claude/settings.local.json`
- Backup: `/home/EchoGloveHugeProjects/.claude/settings.local.json.bak-20260729`

**Interfaces:**
- Consumes: Existing project-local permission settings and project workflow requirements.
- Produces: A short permission list covering read/search, patch/edit, shell/build/test, Git inspection/configuration, graphify, PlatformIO device/build operations, and limited WebFetch/WebSearch.

- [ ] **Step 1: Create a byte-for-byte backup**

Run:
```bash
cp -p /home/EchoGloveHugeProjects/.claude/settings.local.json /home/EchoGloveHugeProjects/.claude/settings.local.json.bak-20260729
```

- [ ] **Step 2: Remove historical one-off permissions**

Replace the 94 accumulated entries with generic project-scoped rules. Do not retain `Bash(git push *)`, destructive reset rules, broad checkout rules, or historical research-domain entries. Preserve explicit permission for `Bash(apply_patch)` and project-scoped Git/graphify/PlatformIO commands needed for the minimum development loop.

- [ ] **Step 3: Validate settings and inspect dangerous entries**

Run:
```bash
python3 -m json.tool /home/EchoGloveHugeProjects/.claude/settings.local.json >/dev/null
rg -n "push|reset --hard|checkout --|force|Co-Authored" /home/EchoGloveHugeProjects/.claude/settings.local.json || true
python3 - <<'PY'
import json
p='/home/EchoGloveHugeProjects/.claude/settings.local.json'
d=json.load(open(p))
allow=d.get('permissions',{}).get('allow',[])
print('allow_count=', len(allow))
for item in allow: print(item)
PY
```
Expected: valid JSON, no destructive Git allowlist entries, and fewer than 25 allow entries.

---

### Task 4: Deduplicate project memory while preserving current operational state

**Files:**
- Modify: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/MEMORY.md`
- Modify or delete: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/echoglove-project-overview.md`
- Modify or delete: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/echoglove-strategy-frozen.md`
- Modify or delete: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/egoglove-monorepo-v7.md`
- Modify: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/handtoken-v2-open-hand-infra.md`
- Modify: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/echoglove-bp-task.md`
- Retain: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/git-identity-discipline.md`
- Retain: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/echoglove-ecosystem-anchors.md`

**Interfaces:**
- Consumes: Current memory facts and repository source-of-truth documents.
- Produces: A short index and operational memories containing only active task state, local environment facts, Git preference, and external verification pointers.

- [ ] **Step 1: Back up all memory files**

Run:
```bash
mkdir -p /root/.claude/projects/-home-EchoGloveHugeProjects/memory/backups-20260729
cp -p /root/.claude/projects/-home-EchoGloveHugeProjects/memory/*.md /root/.claude/projects/-home-EchoGloveHugeProjects/memory/backups-20260729/
```

- [ ] **Step 2: Replace the index with non-duplicative pointers**

`MEMORY.md` should index only the current sprint/protocol state, Git identity discipline, external ecosystem anchors, and BP task status. Each entry must point to a file that still exists.

- [ ] **Step 3: Collapse strategic memories into pointers**

Replace the full strategy and monorepo narratives with short files stating: “Strategic and architectural truth lives in `EgoGlove/docs/V7/STRATEGY.md` and `ARCHITECTURE.md`.” Keep only current branch/commit/task status that is not derivable from repository docs.

- [ ] **Step 4: Remove obsolete V6-only project overview content**

Delete the old project overview if it contains no current operational fact; otherwise replace it with a short note pointing to the V7 monorepo and the current protocol implementation state.

- [ ] **Step 5: Measure memory size and links**

Run:
```bash
wc -l /root/.claude/projects/-home-EchoGloveHugeProjects/memory/*.md
rg -n "echoglove-strategy-frozen|egoglove-monorepo-v7|echoglove-project-overview|handtoken-v2-open-hand-infra" /root/.claude/projects/-home-EchoGloveHugeProjects/memory
```
Expected: total memory text is materially below 307 lines, strategic details are not duplicated, and all retained cross-links resolve.

---

### Task 5: Run final configuration verification and document rollback

**Files:**
- Verify: `/home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md`
- Verify: `/root/.claude/settings.json`
- Verify: `/home/EchoGloveHugeProjects/.claude/settings.local.json`
- Verify: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/`
- Do not modify business code.

**Interfaces:**
- Consumes: Outputs from Tasks 1–4.
- Produces: Verified configuration state and a concise rollback procedure for the user.

- [ ] **Step 1: Validate all JSON files**

Run:
```bash
python3 -m json.tool /root/.claude/settings.json >/dev/null
python3 -m json.tool /home/EchoGloveHugeProjects/.claude/settings.local.json >/dev/null
```
Expected: both commands succeed.

- [ ] **Step 2: Check repository scope and diff**

Run:
```bash
git -C /home/EchoGloveHugeProjects/EgoGlove status --short
find /home/EchoGloveHugeProjects/EgoGlove -path '*/firmware/*' -o -path '*/models/*' -o -path '*/relay/*' -o -path '*/sdk/*' -o -path '*/web/*' | head
```
Expected: only the intended project instruction and plan files are changed in the repository; no business source is modified.

- [ ] **Step 3: Run graphify update only if project files were modified**

Run:
```bash
git -C /home/EchoGloveHugeProjects/EgoGlove status --short -- CLAUDE.md
```
If `CLAUDE.md` changed, run `graphify update /home/EchoGloveHugeProjects/EgoGlove`; otherwise skip. This keeps the project graph current without treating configuration-only work as a firmware build.

- [ ] **Step 4: Report rollback commands**

Rollback commands:
```bash
cp -p /root/.claude/settings.json.bak-20260729 /root/.claude/settings.json
cp -p /home/EchoGloveHugeProjects/.claude/settings.local.json.bak-20260729 /home/EchoGloveHugeProjects/.claude/settings.local.json
rm -rf /root/.claude/projects/-home-EchoGloveHugeProjects/memory
mv /root/.claude/projects/-home-EchoGloveHugeProjects/memory.backup-20260729 /root/.claude/projects/-home-EchoGloveHugeProjects/memory
```
The memory rollback command must be adapted to the actual backup path reported during execution; never run it blindly.
