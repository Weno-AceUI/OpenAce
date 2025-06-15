// /Users/dylando/openace/ui/assets/js/acegui.js

console.log("AceGUI Framework (Web) Loaded");

const AceGUI = {
    version: '0.1.0',

    /**
     * Creates a standard AceGUI button.
     * @param {object} options - Configuration for the button.
     * @param {string} options.text - The text content of the button.
     * @param {function} [options.onClick] - Callback function for click event.
     * @param {string[]} [options.classes] - Additional CSS classes to apply.
     * @returns {HTMLButtonElement} The created button element.
     */
    createButton: function(options = {}) {
        const button = document.createElement('button');
        button.textContent = options.text || 'Button';
        button.classList.add('acegui-button');

        if (options.classes && Array.isArray(options.classes)) {
            options.classes.forEach(cls => button.classList.add(cls));
        }

        if (typeof options.onClick === 'function') {
            button.addEventListener('click', options.onClick);
        }

        return button;
    },

    /**
     * Creates a standard AceGUI panel.
     * @param {object} options - Configuration for the panel.
     * @param {HTMLElement[]} [options.children] - Child elements to append.
     * @param {string[]} [options.classes] - Additional CSS classes (e.g., 'glass').
     * @returns {HTMLDivElement} The created panel element.
     */
    createPanel: function(options = {}) {
        const panel = document.createElement('div');
        panel.classList.add('acegui-panel');

        if (options.classes && Array.isArray(options.classes)) {
            options.classes.forEach(cls => panel.classList.add(cls));
        }

        if (options.children && Array.isArray(options.children)) {
            options.children.forEach(child => panel.appendChild(child));
        }
        return panel;
    },

    /**
     * Creates and shows a modal dialog.
     * @param {object} options - Configuration for the modal.
     * @param {string} [options.title] - The title of the modal.
     * @param {string|HTMLElement} options.content - HTML string or an HTMLElement for the modal body.
     * @param {object[]} [options.buttons] - Array of button configurations for the modal footer.
     *                                      Each button object: {text: string, onClick: function, classes: string[]}
     * @returns {HTMLDivElement} The created modal overlay element.
     */
    showModal: function(options = {}) {
        const overlay = document.createElement('div');
        overlay.className = 'acegui-modal-overlay';

        const modal = document.createElement('div');
        modal.className = 'acegui-modal glass'; // Use .glass for styling

        if (options.title) {
            const titleBar = document.createElement('div');
            titleBar.className = 'acegui-modal-titlebar';
            titleBar.textContent = options.title;
            modal.appendChild(titleBar);
        }

        const contentDiv = document.createElement('div');
        contentDiv.className = 'acegui-modal-content';
        if (typeof options.content === 'string') {
            contentDiv.innerHTML = options.content;
        } else if (options.content instanceof HTMLElement) {
            contentDiv.appendChild(options.content);
        }
        modal.appendChild(contentDiv);

        if (options.buttons && Array.isArray(options.buttons) && options.buttons.length > 0) {
            const footer = document.createElement('div');
            footer.className = 'acegui-modal-footer';
            options.buttons.forEach(btnConfig => {
                const modalButton = this.createButton({
                    text: btnConfig.text,
                    onClick: () => {
                        if (typeof btnConfig.onClick === 'function') {
                            btnConfig.onClick();
                        }
                        overlay.remove(); // Close modal on button click by default
                    },
                    classes: btnConfig.classes || []
                });
                footer.appendChild(modalButton);
            });
            modal.appendChild(footer);
        }

        overlay.appendChild(modal);
        document.body.appendChild(overlay);

        // Optional: Close on Escape key
        const escapeListener = (e) => {
            if (e.key === 'Escape') {
                overlay.remove();
                document.removeEventListener('keydown', escapeListener);
            }
        };
        document.addEventListener('keydown', escapeListener);
        // Optional: Close on overlay click
        overlay.addEventListener('click', (e) => {
            if (e.target === overlay) {
                 overlay.remove();
                 document.removeEventListener('keydown', escapeListener);
            }
        });

        return overlay;
    },

    // Future additions:
    // - List views
    // - Navigation components
    // - Helper functions for system API calls (wrapping window.AppNameAPI_method calls)
    // - State management utilities
};

// Expose AceGUI to the global scope if it's not already (e.g. if using modules later)
if (typeof window !== 'undefined' && !window.AceGUI) {
    window.AceGUI = AceGUI;
}