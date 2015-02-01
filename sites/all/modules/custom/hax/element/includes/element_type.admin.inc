<?php

/**
 * @file
 * Element type editing UI.
 */

/**
 * UI controller.
 */
class ElementTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Element entity types, including adding and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the Element type editing form.
 */
function element_type_form($form, &$form_state, $element_type, $op = 'edit') {
  if ($op == 'clone') {
    $element_type->label .= ' (cloned)';
    $element_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $element_type->label,
    '#description' => t('The human-readable name of this Element type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($element_type->type) ? $element_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'element_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Element type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Element type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function element_type_form_submit(&$form, &$form_state) {
  $element_type = entity_ui_form_submit_build_entity($form, $form_state);
  $element_type->save();
  $form_state['redirect'] = 'admin/structure/element_types';
}

/**
 * Form API submit callback for the delete button.
 */
function element_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/element_types/manage/' . $form_state['element_type']->type . '/delete';
}
